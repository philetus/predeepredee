from xml import sax
from bisect import bisect_left as bisect

from Vertex2 import Vertex2
from Loop2 import Loop2
from Edge2 import Edge2
from Facet2 import Facet2
from Polygon2 import Polygon2

class PolygonParser(sax.ContentHandler):
    """parses closed paths from an svg file into a drawing
    """
    
    def __init__(self, xmlfile, drawing):
        # fill drawing's geometry lists
        self.vertices = drawing.vertices # sorted list of vertices
        self.edges = drawing.edges # sorted list of edges
        self.facets = drawing.facets # sorted list of facets
        self.loops = drawing.loops # chains of vertices in order connected
        self.polygons = drawing.polygons
        
        # parse path vertices into loops
        sax.parse(xmlfile, self)
        
        # discard open loops
        self.loops = [loop for loop in self.loops if loop.closed]
        
        # make sure loops run forwards (counterclockwise)
        for loop in self.loops:
            if not loop.is_forward():
                loop._vertices.reverse()
        
        # find loops that are holes in other loops and build polygons
        self._polygons_from_loops()
        
        # generate facets for each polygon
        for polygon in self.polygons:
            self._facets_from_loops(polygon)
            
    def _facets_from_loops(self, polygon):
        """
        """
        # copy vertices into indirect list
        x = {'pool' : list(polygon.outline)}
        
        ### splice holes into vertex pool
        #
        # ov*, hv* are vertices to splice from outline to hole at, respectively
        #
        # after splice there will be two copies of splice vertices in pool,
        # one at each end of splice: [ ... ov*, hv*, ... hv*, ov*, ... ]
        #
        # [ov0, ov1, ov2, ... ov*, ov*+1, ... ov-1] 
        #                  vvv
        # [ov0, ov1, ... ov*, hv*, hv*+1, ... hv*-1, hv*, ov*, ov*+1, ... ov-1]
        #
        if polygon.holes is not None:
            for hole in sorted(polygon.holes):
                ploop = Loop2(x['pool']) # build loop from current pool
                ov, hv = self._find_splice_pair(ploop, hole)
                
                # get index of outline vertex in pool
                i = x['pool'].index(ov) + 1 # insert past splice vertex
                
                # build splice list
                splice = list(hole)
                j = splice.index(hv)
                splice = splice[j:] + splice[:j] # make hv 1st element of splice
                
                # insert splice into pool with extra [hv, ov] at end
                x['pool'][i:i] = splice + [hv, ov]
        
        # add facets by finding ears
        while len(x['pool']) > 3:
            #print("finding ears in pool size", len(x['pool']))
            
            ploop = Loop2(x['pool'])
            a, b, c = ploop.find_ear()
            
            # drop ear corner from pool list
            #print("pool before dropping {0}:".format((a, b, c)), x['pool'])
            self._drop_ear_corner(x, a, b, c)
            #print("pool after:", x['pool'])
        
            # build facet and component edges and add to polygon
            self._build_facet(polygon, a, b, c)
            
        # build last facet from last 3 vertices in pool
        self._build_facet(polygon, *x['pool'])

    def _build_facet(self, polygon, a, b, c):
        edges = []
        last = c
        for v in (a, b, c):
            edge = self._add_edge(last, v)
            edges.append(edge)
            last = v
        facet = self._add_facet(*edges)
        
        # add edges and facet to polygon
        polygon._edges += edges
        polygon._facets.append(facet)
        
    def _drop_ear_corner(self, x, a, b, c):
        i = x['pool'].index(b)
        
        # if first b not flanked by a and c, recurse until we find it
        if not(x['pool'][i - 1] == a and x['pool'][i + 1] == c):
            #print("\trecursing to drop ear corner!")
            
            y = {'pool' : x['pool'][i + 1:]}
            self._drop_ear_corner(y, a, b, c)
            x['pool'] = x['pool'][:i + 1] + y['pool']
            return
        
        # if b is flanked by a and c remove it
        x['pool'] = x['pool'][:i] + x['pool'][i + 1:]
            
    def _find_splice_pair(self, outline, hole):
        """return closest (outline_vertex, hole_vertex) to splice at
        """
        # start with min hole vertex
        hole_v = min(hole._vertices)
        hole_vs = (v for v in hole if v != hole_v)
        
        # find outline vertex closest to initial hole vertex
        outline_vs = iter(outline)
        outline_v = outline_vs.next()
        distance = (hole_v - outline_v).magnitude
        for v in outline_vs:
            d = (hole_v - v).magnitude
            if d < distance:
                distance = d
                outline_v = v
        
        # find hole vertex closest to outline vertex
        for v in hole_vs: # iterator over all but first hole vertex
            d = (v - outline_v).magnitude
            if d < distance:
                distance = d
                hole_v = v
        
        return outline_v, hole_v
        
    def _polygons_from_loops(self):
        """
        """
        top = [] # top level loops
        
        # check each loop to see if it is surrounded by any other
        for loop in self.loops:
            if not self._loop_is_surrounded(loop):
                top.append(loop)
        
        # find children of each top level loop and build polygons
        searchlist = [l for l in self.loops if l not in top]
        for loop in top:
            children = [] # children of this loop
            
            # find child loops
            for other in searchlist:
                if loop.surrounds(other):
                    children.append(other)
            
            # remove children from searchset
            searchlist = [l for l in searchlist if l not in children]
            
            # reverse hole loop vertices
            for child in children:
                child._vertices.reverse()
            
            if len(children) < 1:
                children = None
            
            # create polygon from loops
            polygon = Polygon2(loop, children)
            
            # add to polygon list
            self.polygons.append(polygon)
            
    
    def _loop_is_surrounded(self, loop):
        for other in (l for l in self.loops if l != loop):
            if other.surrounds(loop):
                return True
        return False
            
    def _parse_path(self, dstring, idstring):
        """parse 'd' attribute of path tag
        """
        # split attr string on whitespace
        dlist = dstring.split()
                
        # parser for "m" (inkscape format)
        if dlist[0] == "m" or dlist[0] == "M":
            self._parse_mpath(dlist, idstring)
            return
            
        raise ValueError("unrecognized d attr init: {0}".format(dlist[0]))
        
    def _parse_mpath(self, dlist, idstring):
        """parse path from inkscape-style d attr list
           'm x,y dx,dy dx,dy ... [z]'
        """
        relative = True
        
        # discard initial m
        if dlist.pop(0) == "M":
            relative = False
        
        # loop to fill with vertices
        loop = Loop2(idstring=idstring)

        # set initial vertex
        x, y = (float(s) for s in dlist.pop(0).split(","))
        current_vertex = self._add_vertex(x, y)
        last_vertex = None
        
        # discard loop closed tag as they already are
        if dlist[-1] == "z":
            dlist.pop()
        
        for item in dlist:
            if item == "l":
                relative = True
            elif item == "L":
                relative = False
            elif "," in item:
                x, y = (float(s) for s in item.split(","))
                last_vertex = current_vertex
                if relative:
                    current_vertex = self._add_vertex(x + last_vertex.x, 
                                                      y + last_vertex.y)
                else:
                    current_vertex = self._add_vertex(x, y)
                    
                if not loop.add_pair(last_vertex, current_vertex):
                    raise ValueError(
                        "wtf? can't add pair to loop {0}!".format(idstring))
            
            else:
                raise ValueError("can't parse d attr item: {0}".format(item))
            
        # append loop to big list of loops
        self.loops.append(loop)
        
    def _add_vertex(self, x, y):
        """return vertex at coords, create it if it isn't already there
        """
        v = Vertex2(x, y)
        i = bisect(self.vertices, v)
        
        # if vertex at these coordinates exists just return it
        if len(self.vertices) > i and self.vertices[i] == v:
            return self.vertices[i]
        
        # otherwise add new vertex in sorted position and return it
        self.vertices.insert(i, v)
        return v
    
    def _add_edge(self, a, b):
        """return edge between vertices, create it if it's not there
        """
        e = Edge2(a, b)
        i = bisect(self.edges, e)
        
        # if edge between these vertices exists just return it
        if len(self.edges) > i and self.edges[i] == e:
            return self.edges[i]
        
        # otherwise add new edge in sorted position and return it
        self.edges.insert(i, e)
        return e
    
    def _add_facet(self, ea, eb, ec):
        """return facet containing given edges, create it if its not there
        """
        f = Facet2(ea, eb, ec)
        i = bisect(self.edges, f)
        if len(self.facets) > i and self.facets[i] == f:
            return self.facets[i]
        
        self.facets.insert(i, f)
        return f

    ###
    ### sax contenthandler interface for parsing xml file
    ###
    
    def startElement(self, name, attrs):
        #print("starting element", str(name))
        if str(name) == "path":
            self._parse_path(str(attrs["d"]), str(attrs["id"]))
    


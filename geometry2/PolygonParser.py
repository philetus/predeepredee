from xml import sax
from bisect import bisect_left as bisect

from Vertex2 import Vertex2
from Loop2 import Loop2
from Edge2 import Edge2
from Polygon2 import Polygon2

class PolygonParser(sax.ContentHandler):
    """parses closed paths from an svg file into a drawing
    """
    
    def __init__(self, xmlfile, drawing):
        self.drawing = drawing

        self.vertices = [] # sorted list of vertices
        self.edges = [] # sorted list of edges
        self.facets = [] # sorted list of facets
        self.polygons = []
        
        # for construction
        self.loops = [] # chains of vertices in order connected
        
        # parse vertices into temporary loops
        sax.parse(xmlfile, self)
        
        # discard open loops
        self.loops = [loop for loop in self.loops if loop.closed]
        
        # make sure loops run forwards (counterclockwise)
        for loop in self.loops:
            if not loop.is_forward():
                loop._vertices.reverse()
        
        # find loops that are holes in other loops
        # and build polygons
        self.polygons_from_loops()
    
    def startElement(self, name, attrs):
        #print "starting element", str(name)
        if str(name) == "path":
            self.parse_path(str(attrs["d"]))
    
    def polygons_from_loops(self):
        """
        """
        top = [] # top level loops
        
        # check each loop to see if it is surrounded by any other
        for loop in self.loops:
            if not self._loop_is_surrounded(loop):
                top.append(loop)
        
        # find children of each top level loop and build polygons
        searchset = set(self.loops) - set(top)
        for loop in top:
            children = [] # children of this loop
            
            # find child loops
            for other in searchset:
                if loop.surrounds(other):
                    children.append(other)
            
            # remove children from searchset
            searchset -= set(children)
            
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
    
    def parse_path(self, dstring):
        """parse 'd' attribute of path tag
        """
        # split attr string on whitespace
        dlist = dstring.split()
                
        # parser for "m" (inkscape format)
        if dlist[0] == "m" or dlist[0] == "M":
            self.parse_mpath(dlist)
            return
            
        raise ValueError("unrecognized d attr init: {0}".format(dlist[0]))
        
    def parse_mpath(self, dlist):
        """parse path from inkscape-style d attr list
           'm x,y dx,dy dx,dy ... [z]'
        """
        relative = True
        
        # discard initial m
        if dlist.pop(0) == "M":
            relative = False
        
        # loop to fill with vertices
        loop = Loop2()    

        # set initial vertex
        x, y = (float(s) for s in dlist.pop(0).split(","))
        current_vertex = self.add_vertex(x, y)
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
                    current_vertex = self.add_vertex(x + last_vertex.x, 
                                                     y + last_vertex.y)
                else:
                    current_vertex = self.add_vertex(x, y)
                    
                if not loop.add_pair(last_vertex, current_vertex):
                    raise ValueError("wtf? can't add pair to loop!")
            
            else:
                raise ValueError("can't parse d attr item: {0}".format(item))
            
        # append loop to big list of loops
        self.loops.append(loop)
        
    def add_vertex(self, x, y):
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
    
    def add_edge(self, a, b):
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
    


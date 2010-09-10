from __future__ import print_function

from Canvas import Canvas

class DrawingWindow(Canvas):
    """displays a drawing
    """
    POLYGON_FILL = (0.0, 0.7, 0.5, 0.5)
    EDGE_SIZE = 0.5
    EDGE_COLOR = (0.9, 0.0, 0.5, 0.7)
    
    def __init__(self, drawing):
        Canvas.__init__(self)
        self.drawing = drawing
        
    def handle_draw(self, brush):
        """render drawing to canvas with brush
        """
        for polygon in self.drawing.polygons:
            self.draw_polygon(brush, polygon)
    
    
    def draw_polygon(self, brush, polygon):
        """render a polygon to canvas
        """
        # fill polygons
        if polygon.outline is None:
            print("polygon has no outline!")
            return
            
        # draw outside loop
        self._path_from_loop(brush, polygon.outline)
        
        # draw inside loops
        if polygon.holes is not None:
            for hole in polygon.holes:
                self._path_from_loop(brush, hole)
        
        # fill polygon
        brush.color = self.POLYGON_FILL
        brush.fill_path()
        brush.clear_path()
        
        # render vertices
        
        # render edges
        brush.color = self.EDGE_COLOR
        brush.size = self.EDGE_SIZE
        for edge in polygon._edges:
            brush.move_to(*edge.a)
            brush.path_to(*edge.b)
            brush.stroke_path()
            brush.clear_path()
        
        # render loops

    def _path_from_loop(self, brush, loop):
        """render a loop as a path
        """
        vs = iter(loop)
        brush.move_to(*vs.next()) # move to first vertex
        for v in vs:
            brush.path_to(*v)
        brush.close_path()
        
    def handle_quit(self):
        """kill gooey when window is closed
        """
        self.stop()
        return True


from Canvas import Canvas

class DrawingWindow(Canvas):
    """displays a drawing
    """
    POLYGON_FILL = (0.0, 0.9, 0.5, 0.7)
    
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
        
        # render loops

    def _path_from_loop(self, brush, loop):
        """render a loop as a path
        """
        vs = loop.vertices
        brush.move_to(*vs.next()) # move to first vertex
        for v in vs:
            brush.path_to(*v)
        brush.close_path()
        
    def handle_quit(self):
        """kill gooey when window is closed
        """
        self.stop()
        return True


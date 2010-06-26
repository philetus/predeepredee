from Shape2 import Shape2

class Polygon2(Shape2):
    """a closed shape
    """
    
    def __init__(self, outline, holes=None):
        Shape2.__init__(self)
        self.outline = outline
        self.holes = holes

from __future__ import print_function

from Shape2 import Shape2

class Polygon2(Shape2):
    """a closed shape
    """
    
    def __init__(self, outline, holes=None):
        Shape2.__init__(self) # inits the following:
        #self._vertices = []
        #self._bounds = None

        self._edges = []
        self._facets = []

        self.outline = outline
        self.holes = holes

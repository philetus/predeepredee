from Bounds2 import Bounds2

class Shape2:
    """abstract superclass for shapes defined over vertices and straight edges
    """
    
    def __init__(self):
        self._vertices = []
        self._bounds = None
    
    @property
    def vertices(self):
        """iterate over vertices of shape
        """
        for vertex in self._vertices:
            yield vertex
            
    @property
    def vertex_len(self):
        return len(self._vertices)
            
    @property
    def bounds(self):
        """return bounds of shape
        """
        if self._bounds is None:
            self._bounds = Bounds2(cloud=self.vertices)
        return self._bounds
    

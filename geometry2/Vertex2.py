from Vector2 import Vector2

class Vertex2(Vector2):
    """a point on a 2d plane
    """
    
    EPSILON = 0.1 # coords nearer than epsilon are considered the same

    def __init__(self, x, y):
        Vector2.__init__(self, x, y)
        
        self.loop = None
        self.edges = set()

    def __repr__(self):
        return "<v {0:.1f} {1:.1f}>".format(*self)
        
    ###
    ### vertices with both coords within epsilon are equal
    ###
    
    def __cmp__(self, other):
        cx = self._cmp_coord(self.x, other.x)
        if cx != 0:
            return cx
        return self._cmp_coord(self.y, other.y)
    
    def _cmp_coord(self, a, b):
        d = a - b
        if abs(d) < self.EPSILON:
            return 0
        if a < b:
            return -1
        return 1
    

from Vertex2 import Vertex2

class Bounds2:
    """a 2d bounding box
    """
    
    def __init__(self, mn=None, mx=None, cloud=None):
        self.min = None
        self.max = None
        if mn and mx:
            self.min = Vertex2(*mn)
            self.max = Vertex2(*mx)
        elif cloud:
            xs = []
            ys = []
            for x, y in cloud: # iterate over each vertex in cloud to get x, y
                xs.append(x)
                ys.append(y)
            self.min = Vertex2(min(xs), min(ys))
            self.max = Vertex2(max(xs), max(ys))
        else:
            raise ValueError("insufficient data to init bounds!")
    
    def touches(self, bounds):
        """return true if given bounding box touches this one
        """
        if self.min.x > bounds.max.x:
            return False
        if self.max.x < bounds.min.x:
            return False
        if self.min.y > bounds.max.y:
            return False
        if self.max.y < bounds.min.y:
            return False
        return True

    def contains(self, vertex):
        """return true if vertex lies within bounds
        """
        if(self.min.x <= vertex.x and vertex.x <= self.max.x and 
           self.min.y <= vertex.y and vertex.y <= self.max.y):
            return True
        return False

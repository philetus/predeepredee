from bisect import bisect_left as bisect
from Vertex import Vertex
from Edge import Edge

class Drawing:
    """a vector drawing consisting of a set of polygons
    """
    
    def __init__(self):    
        self.vertices = [] # sorted list of vertices
        self.edges = [] # sorted list of edges
        self.polygons = [] 
            


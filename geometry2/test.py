from PolygonParser import PolygonParser
from Drawing import Drawing

from Gooey import Gooey
from DrawingWindow import DrawingWindow

d = Drawing()
p = PolygonParser("tricky_polygon.svg", d)

g = Gooey()
dw = DrawingWindow(d)
dw.zoom = 1.0
g.show(dw)

g.start()


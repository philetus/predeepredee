from PolygonParser import PolygonParser
from Drawing import Drawing

from Gooey import Gooey
from DrawingWindow import DrawingWindow

d = Drawing()
p = PolygonParser("cockroach.svg", d)

g = Gooey()
dw = DrawingWindow(d)
dw.zoom = 1.5
g.show(dw)

g.start()


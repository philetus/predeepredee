CPPFLAGS += -W -Wall -g -O3
CPPFLAGS += `pkg-config --cflags sdl cairo bullet`
CPP = g++
OFLAG = -o
LIBRARIES = `pkg-config --libs sdl cairo bullet` -lGLU
.SUFFIXES : .o .cpp
.cpp.o : $(CPP) $(CPPFLAGS) -c $<

TARGETS=box_test

all: $(TARGETS)

box_test: box_test.o Gooey.o WorldWindow.o World.o renderer/TargetCamera.o \
    renderer/ThingDrawer.o renderer/WorldRenderer.o things/Box.o \
    things/Thing.o geometry3/Facet.o geometry3/Vector3.o 
	$(CPP) $(OFLAG)$@ $+ $(LIBRARIES)

box_test.o: box_test.cpp Window.h WorldWindow.h World.h \
    renderer/TargetCamera.h renderer/ThingDrawer.h renderer/WorldRenderer.h \
    things/Box.h

Gooey.o: Gooey.cpp Gooey.h World.h Window.h things/Thing.h

WorldWindow.o: WorldWindow.cpp WorldWindow.h Window.h World.h \
    renderer/Camera.h renderer/WorldRenderer.h geometry3/Vector3.h \
    geometry3/Rotation3.h geometry3/Transformation3.h things/Box.h \
    things/Flexure.h

World.o: World.cpp World.h things/Thing.h \
    things/AtomicThing.h things/CompositeThing.h things/Box.h \
    things/SoftThing.h things/RigidThing.h \
    util/Iterator.h util/DequeIterator.h geometry3/Vector3.h \
    geometry3/Rotation3.h geometry3/Transformation3.h

renderer/TargetCamera.o: renderer/TargetCamera.cpp renderer/TargetCamera.h \
    renderer/Camera.h renderer/Light.h geometry3/Vector3.h geometry3/Rotation3.h \
    geometry3/Matrix3x3.h
    
renderer/ThingDrawer.o: renderer/ThingDrawer.cpp renderer/ThingDrawer.h \
    util/Iterator.h geometry3/Facet.h things/Thing.h things/AtomicThing.h \
    things/CompositeThing.h

renderer/WorldRenderer.o: renderer/WorldRenderer.cpp renderer/WorldRenderer.h \
    renderer/Light.h renderer/Camera.h renderer/ThingDrawer.h World.h \
    geometry3/Vector3.h util/DequeIterator.h

things/Thing.o: things/Thing.cpp things/Thing.h geometry3/Transformation3.h

things/Box.o: things/Box.cpp things/Box.h things/RigidThing.h \
    util/Iterator.h geometry3/Vector3.h geometry3/Transformation3.h \
    geometry3/Facet.h

geometry3/Facet.o: geometry3/Facet.cpp geometry3/Facet.h geometry3/Vector3.h \
    util/Iterator.h
    
geometry3/Vector3.o: geometry3/Vector3.cpp geometry3/Vector3.h

clean:
	$(RM) $(TARGETS)
	$(RM) *.o renderer/*.o things/*.o geometry3/*.o
	$(RM) *~

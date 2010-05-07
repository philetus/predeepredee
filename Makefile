CPPFLAGS += -W -Wall -g -O3
CPPFLAGS += `pkg-config --cflags sdl cairo bullet`
CPP = g++
OFLAG = -o
LIBRARIES = `pkg-config --libs sdl cairo bullet` -lGLU
.SUFFIXES : .o .cpp
.cpp.o : $(CPP) $(CPPFLAGS) -c $<

TARGETS=box_test flexure_test constraint_test

all: $(TARGETS)

box_test: box_test.o RootDemon.o WorldWindow.o World.o renderer/TargetCamera.o \
    renderer/ThingDrawer.o renderer/WorldRenderer.o things/Box.o \
    things/Thing.o geometry/Facet.o geometry/Vector3.o 
	$(CPP) $(OFLAG)$@ $+ $(LIBRARIES)

box_test.o: box_test.cpp Window.h WorldWindow.h World.h \
    renderer/TargetCamera.h renderer/ThingDrawer.h renderer/WorldRenderer.h \
    things/Box.h

WorldWindow.o: WorldWindow.cpp WorldWindow.h Window.h World.h \
    renderer/Camera.h renderer/WorldRenderer.h geometry/Vector3.h \
    geometry/Rotation3.h geometry/Transformation3.h things/Box.h \
    things/Flexure.h

World.o: World.cpp World.h things/Thing.h \
    things/AtomicThing.h things/CompositeThing.h things/Box.h \
    things/SoftThing.h things/RigidThing.h \
    util/Iterator.h util/DequeIterator.h geometry/Vector3.h \
    geometry/Rotation3.h geometry/Transformation3.h

renderer/TargetCamera.o: renderer/TargetCamera.cpp renderer/TargetCamera.h \
    renderer/Camera.h renderer/Light.h geometry/Vector3.h geometry/Rotation3.h \
    geometry/Matrix3x3.h
    
renderer/ThingDrawer.o: renderer/ThingDrawer.cpp renderer/ThingDrawer.h \
    util/Iterator.h geometry/Facet.h things/Thing.h things/AtomicThing.h \
    things/CompositeThing.h

renderer/WorldRenderer.o: renderer/WorldRenderer.cpp renderer/WorldRenderer.h \
    renderer/Light.h renderer/Camera.h renderer/ThingDrawer.h World.h \
    geometry/Vector3.h util/DequeIterator.h

things/Thing.o: things/Thing.cpp things/Thing.h geometry/Transformation3.h

things/Box.o: things/Box.cpp things/Box.h things/RigidThing.h \
    util/Iterator.h geometry/Vector3.h geometry/Transformation3.h \
    geometry/Facet.h

geometry/Facet.o: geometry/Facet.cpp geometry/Facet.h geometry/Vector3.h \
    util/Iterator.h
    
geometry/Vector3.o: geometry/Vector3.cpp geometry/Vector3.h

clean:
	$(RM) $(TARGETS)
	$(RM) *.o renderer/*.o things/*.o geometry/*.o
	$(RM) *~

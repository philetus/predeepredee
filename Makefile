CPPFLAGS += -W -Wall -g -O3
CPPFLAGS += `pkg-config --cflags sdl cairo bullet`
CPP = g++
OFLAG = -o
LIBRARIES = `pkg-config --libs sdl cairo bullet` -lGLU
.SUFFIXES : .o .cpp
.cpp.o : $(CPP) $(CPPFLAGS) -c $<

TARGETS=box_test

all: $(TARGETS)

box_test: box_test.o Window.o World.o TargetCamera.o ThingDrawer.o \
    things/Box.o
	$(CPP) $(OFLAG)$@ $+ $(LIBRARIES)

box_test.o: box_test.cpp Window.h World.h TargetCamera.h ThingDrawer.h \
    things/Box.h

Window.o: Window.cpp Window.h World.h Camera.h ThingDrawer.h

World.o: World.cpp World.h ThingMotionState.h things/Thing.h \
    things/AtomicThing.h things/CompositeThing.h things/Box.h \
    util/Iterator.h util/DequeIterator.h geometry/Vector3.h \
    geometry/Rotation3.h geometry/Transformation3.h

TargetCamera.o: TargetCamera.cpp TargetCamera.h Camera.h Light.h \
    geometry/Vector3.h geometry/Rotation3.h geometry/Matrix3x3.h
    
ThingDrawer.o: ThingDrawer.cpp ThingDrawer.h util/Iterator.h geometry/Facet.h \
    things/Thing.h things/AtomicThing.h things/CompositeThing.h

things/Box.o: things/Box.cpp things/Box.h things/AtomicThing.h \
    util/Iterator.h geometry/Vector3.h geometry/Transformation3.h \
    geometry/Facet.h
    
clean:
	$(RM) $(TARGETS)
	$(RM) *.o
	$(RM) *~

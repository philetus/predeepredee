CFLAGS += -W -Wall -g -O3
CFLAGS += `pkg-config --cflags sdl cairo`
CPP = g++

TARGETS=test_window

all: $(TARGETS)

test_window: test_window.o ../Window.cpp
	$(CPP) -o $@ $+ `pkg-config --libs sdl cairo`

clean:
	$(RM) $(TARGETS)
	$(RM) *.o
	$(RM) *~

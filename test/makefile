APP		=	gl-cairo-simple

CPP		=	g++

CFLAGS	=	-Wall -c -g -std=c99 \
			`sdl-config --cflags` \
			`pkg-config --cflags cairo`

LDFLAGS	=	`sdl-config --libs` \
			`pkg-config --libs cairo` \
			-lGL -lGLU -lm

SRCS	=	test.c # \
#           test2.c

OBJS	=	$(SRCS:.c=.o)

all: $(APP)

.cpp.o:
	$(CPP) $(CFLAGS) -c $< -o $@
.c.o:
	$(CPP) $(CFLAGS) -c $< -o $@

# it is important that $(OBJS) stands _before_ $(LDFLAGS)
$(APP):	$(OBJS)
	$(CPP) $(OBJS) $(LDFLAGS) -o$(APP)

clean:
	rm -f *.o  *~ $(APP) frame.png


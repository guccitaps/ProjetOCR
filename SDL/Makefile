 CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl --libs gtk+-2.0` -MMD
CFLAGS= -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm
 
OBJ= pixel_operations.o image_section.o main.o
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main
 
-include ${DEP}
 
# END

 CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm
 
OBJ= pixel_operations.o image_section.o main.o ../neuralNetwork/network.o
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}

test:
	gcc main.c pixel_operations.c image_section.c `pkg-config --libs sdl` -lSDL_image -lm -o test
 
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main
 
-include ${DEP}
 
# END


 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS=  -lm
 
OBJ= neural
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}

test:
	gcc -std=c99 network.c  -lm -o network
test2: 
	gcc -std=c99 matrix.c  -lm -o network
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} network
-include ${DEP}
 
# END


 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS=  -lm
 
OBJ= neural
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} neural
 
-include ${DEP}
 
# END

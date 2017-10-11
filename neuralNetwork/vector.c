#include <stdio.h>
#include <stdlib.h>

struct Coord {
unsigned long x;
unsigned long y;
};

struct Vector {
struct Coord start;
struct Coord end;
} ;

void Coord_Init(struct Coord coo, unsigned long x, unsigned long y)
{
	coo.x = x;
	coo.y = y;
}

void Vector_Init(struct Vector v, unsigned long x, unsigned long y, unsigned long x2, unsigned long y2)
{
	Coord_Init(v.start, x, y);
	Coord_Init(v.end, x2, y2);
}

int main(int argc, char* argv[])
{
	
}

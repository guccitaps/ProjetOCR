#include <stdio.h>
#include <stdlib.h>

struct Coord {
unsigned long x;
unsigned long y;
};

struct Vector {
struct Coord start;
struct Coord end;

unsigned long length; //sqrt((end.x - start.c)^2 + (end.y - start.y)^2)
unsigned long direction; // 0  pi/4  pi/2  3pi/4
unsigned long density; //amount of other Vectors assimilated

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

bool Mergeable(struct Vector u, struct Vector v)
{

	
}

int main(int argc, char* argv[])
{
	
}

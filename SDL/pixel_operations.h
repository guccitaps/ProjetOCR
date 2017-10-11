// pixel_operations.h
 
# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <SDL.h>
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
Uint32 greyconvert(Uint32 pixel, SDL_Surface* screen);
void forall_greyconvert(SDL_Surface* screen);
void sobel_filter(SDL_Surface* screen, SDL_Surface* screen2, _Bool x, _Bool y);
 
# endif

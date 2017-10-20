// pixel_operations.h
 
# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <SDL.h>


typedef Uint32 (*func_t)(Uint32, SDL_Surface*); 
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
Uint32 greyconvert(Uint32 pixel, SDL_Surface* screen);
Uint32 black_or_white(Uint32 pixel, SDL_Surface* screen);
void forall_func(SDL_Surface* screen, func_t f);
void sobel_filter(SDL_Surface* screen, SDL_Surface* screen2, _Bool x, _Bool y);
 
# endif

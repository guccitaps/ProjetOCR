
# ifndef IMAGE_SECTION_H_
# define IMAGE_SECTION_H_

# include <stdio.h> 
# include <stdlib.h>
# include <SDL.h>

void bloc_detection(SDL_Surface* screen, char screen_matrix[], char divisor);

size_t block_merging(SDL_Surface* screen,  char matrix[], size_t w, size_t h, size_t tab[]);

void block_colorizing(SDL_Surface* screen, size_t divisor, size_t tab[], size_t len);

size_t cutlines(size_t lineslist[], size_t bloc[], SDL_Surface* screen);

size_t cutchar(size_t charlist[], size_t bloc[], SDL_Surface* screen);

size_t cutimage(size_t result[], size_t bloclist[], size_t len, SDL_Surface* screen);

void bloc_colorizing(SDL_Surface* screen, size_t tab[], size_t len);

void char_colorizing(SDL_Surface* screen, size_t tab[], size_t len);

SDL_Surface* SDL_ScaleSurface (SDL_Surface* s, Uint16 w, Uint16 h);

char* create_list_matrix( SDL_Surface* s);
# endif

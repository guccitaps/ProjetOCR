
# ifndef IMAGE_SECTION_H_
# define IMAGE_SECTION_H_

# include <stdio.h> 
# include <stdlib.h>
# include <SDL.h>

void bloc_detection(SDL_Surface* screen, char screen_matrix[], char divisor);

size_t block_merging( char matrix[], size_t w, size_t h, size_t tab[]);

void block_colorizing(SDL_Surface* screen, size_t divisor, size_t tab[], size_t len);
# endif

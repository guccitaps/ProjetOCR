# ifndef CHARCUT_H_
# define CHARCUT_H_

# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>

size_t cutlines(size_t lineslist[], size_t bloc[], SDL_Surface* screen);

size_t cutchar(size_t charlist[], size_t bloc[], SDL_Surface* screen);

void cutimage(size_t result[], size_t bloclist[], size_t len, SDL_Surface* screen);
# endif

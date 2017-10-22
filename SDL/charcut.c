#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "pixel_operations.h"
#include "charcut.h"

/*int[][] recognize(char array[], size_t lines, size_t cols)
{
	int result[lines*cols][2];
	int count = 0;
	int line = 0;
	for(int i = 0; i<lines; i++)
	{
		
		
		if (line == 1)
		{
			result[count] = -1;
		}
		line = 1;
		for(int j = 0; j<cols; j++)
		{
			if (array[j + i * cols]==1)
			{
				line = 0;
				int coord[] = around(array[], cols, i, j);
			}
		}
}

int[] around(char array[], size_t cols, size_t i, size_t j)
{
	int result[];
	if(array[j+1 + i * cols] == 1)
	{
		result[0] = i;
		result[1] = j+1;
		return result;
	}
	if(array[j-1 + i * cols] == 1)
        {
                result[0] = i;
                result[1] = j-1;
                return result;
        }
	if(array[j + (i+1) * cols] == 1)
        {
                result[0] = i+1;
                result[1] = j;
                return result;
        }
	if(array[j + (i-1) * cols] == 1)
        {
		result[0] = i-1;
		result[1] = j;
		return result;
	}
}*/

//#define N 4

size_t cutlines(size_t lineslist[], size_t bloc[], SDL_Surface* screen)
{
	//size_t[100][4] lineslist;
	int previous = 1;
	int whiteline;
	size_t compteur = 0;
	size_t line[4];
	for (size_t i = bloc[2]; i < bloc[3]; i++)
	{
		whiteline = 1;
		for (size_t j = bloc[0]; j < bloc[1]; j++)
		{
			Uint32 pixel = getpixel(screen, i, j);
                        // restriction : au moindre pixel noir -> caractere -> bloc de texte
                        Uint8 red = 0;
                        SDL_GetRGB(pixel, screen->format, &red, &red, &red);
                        if (red == 0)
			{
				whiteline = 0;
			}
		}
		if(whiteline == 0)
		{
			if(previous == 1)
			{
				//size_t line[4] = {0, 0, 0, 0};
				line[0] = bloc[0];
				line[1] = bloc[1];
				line[2] = i; 
			}
		}
		else
		{
			if(previous == 0)
			{
				line[3] = i;
				lineslist[compteur] = line[0];
				lineslist[compteur + 1] = line[1];
				lineslist[compteur + 2] = line[2];
				lineslist[compteur + 3] = line[3];
				compteur += 4;	
			}
		}
		previous = whiteline;
	}
	//return lineslist;
	//return 1;
	return compteur;
}

size_t cutchar(size_t charlist[], size_t bloc[], SDL_Surface* screen)
{
	//size_t[100][4] charlist;
	int previous  = 1;
	int whiteline;
	size_t compteur = 0;
	size_t carac[4];
	for (size_t j = bloc[0]; j < bloc[1]; j++)
	{
		whiteline = 1;
		for (size_t i = bloc[2]; i < bloc[3]; i++)
		{
			Uint32 pixel = getpixel(screen, i, j);
                        // restriction : au moindre pixel noir -> caractere -> bloc de texte
                        Uint8 red = 0;
                        SDL_GetRGB(pixel, screen->format, &red, &red, &red);
                        if (red == 0)
                        {
                                whiteline = 0;
                        }

		}
		if(whiteline == 0)
                {
                        if(previous == 1)
                        {
                                carac[2] = bloc[2];
                                carac[3] = bloc[3];
                                carac[0] = j;
                        }
                }
                else
                {
                        if(previous == 0)
                        {
                                carac[1] = j;
				charlist[compteur] = carac[0];
				charlist[compteur + 1] = carac[1];
				charlist[compteur + 2] = carac[2];
				charlist[compteur + 3] = carac[3];
				compteur += 4;
                        }
                }
                previous = whiteline;
	}
	//return charlist;
	return compteur;
} 

void cutimage(size_t result[], size_t bloclist[], size_t len, SDL_Surface* screen)
{
	size_t lenresult = 0;
	for(size_t i = 0; i < len; i += 4)
	{
		size_t lineslist[100];
		size_t bloccoord[4] = {bloclist[i], bloclist[i+1], bloclist[i+2], bloclist[i+3]};
		size_t lenlines = cutlines(lineslist, bloccoord, screen);
		for(size_t j = 0; j < lenlines; j += 4)
		{
			size_t charlist[150];
			size_t linecoord[4] ={lineslist[j], lineslist[j+1], lineslist[j+2], lineslist[j+3]}; 
			size_t charlen = cutchar(charlist, linecoord, screen);
			//lenresult += charlen;
			size_t o = lenresult;
			for(; lenresult <(lenresult + charlen); lenresult++)
			{
				result[lenresult] = charlist[lenresult - o];
			}
		}
	}
}

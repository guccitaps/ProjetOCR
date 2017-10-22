#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

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

size_t[][] cutlines(size_t[] bloc, SDL_Surface* image)
{
	size_t[100][4] result;
	int previous = 1;
	int whiteline;
	for (size_t i = bloc[0]; i < bloc[1]; i++)
	{
		whiteline = 1;
		for (size_t j = bloc[2]; j < bloc[3]; j++)
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
				size_t[4] line;
				line[0] = bloc[0];
				line[1] = bloc[1];
				line[2] = i; 
			}
		}
		else
		{
			if(previous = 0)
			{
				line[3] = i;	
			}
		}
		previous = whiteline;
	}
	return result;
}

size_t[][] cutchar(size_t[] bloc, SDL_Surface* image)
{
	size_t[100][4] result;
	int previous  = 1;
	int whiteline;
	for (size_t j = bloc[2]; j < bloc[3]; j++)
	{
		whiteline = 1;
		for (size_t i = bloc[0]; i < bloc[1]; i++)
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
                                size_t[4] carac;
                                carac[0] = bloc[2];
                                carac[1] = bloc[3];
                                carac[2] = i;
                        }
                }
                else
                {
                        if(previous = 0)
                        {
                                line[3] = i;
                        }
                }
                previous = whiteline;
	}
} 
/*size_t[][][] main()*/

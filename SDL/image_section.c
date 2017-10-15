#include <stdio.h>
#include <stdlib.h>

#include "pixel_operations.h"
#include "image_section.h"

/*
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
*/

void bloc_detection(SDL_Surface* screen, char screen_matrix[])
{

  const int divisor = 8; // 8 arbitraire, on teste

  size_t w = screen->w;
  size_t h = screen->h;

  size_t matrix_w = w / divisor;
  size_t matrix_h = h / divisor;
  
  screen_matrix = malloc(matrix_w * matrix_h);

  if (screen_matrix == NULL)
  {
	printf("echec allocation memoire");
	exit(0);
  }

  for (char i = 0; i < divisor; i++)
  {
	for(char j = 0; j < divisor; j++)
	{
		unsigned upper_limit_w = i == divisor-1 ? w : (i + 1) * matrix_w; //gestion derniere case : plus grande que les autres.
		unsigned upper_limit_h = j == divisor-1 ? h : (j + 1) * matrix_h;
		
		char force_exit = 0;
		for(unsigned k = i * matrix_w; k < upper_limit_w; k++)
		{
			for(unsigned l = j * matrix_h; l < upper_limit_h; l++)
			{
				Uint32 pixel = getpixel(screen, k, l);
				// restriction : au moindre pixel noir -> caractere -> bloc de texte
				Uint8 red = 0;
				SDL_GetRGB(pixel, screen->format, &red, &red, &red);
				if (red == 0) //pixel noir detecte -> texte
				{
					force_exit = 1;	
					break;
				} 
			}
			if(force_exit)
			{
				break;
			}
		}
		
		if(force_exit)
		{
			screen_matrix[i + j * divisor] = 1;
			break;
		}
		else
		{
			screen_matrix[i + j * divisor] = 0;
		}
	} 
  }
}

/*
int main(int argc, char* argv[])
{
	if (argc)
	{
		free(argv);
	}
  
  
	return 0;
}
*/




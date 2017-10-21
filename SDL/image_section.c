#include <stdio.h>
#include <stdlib.h>

#include "pixel_operations.h"
#include "image_section.h"

/*
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
*/

void bloc_detection(SDL_Surface* screen, char screen_matrix[], char divisor)
{
  Uint32 pixel = SDL_MapRGB(screen->format, 150, 150, 0);
  size_t w = screen->w;
  size_t h = screen->h;

  size_t matrix_w = w / divisor;
  size_t matrix_h = h / divisor;
  
//  screen_matrix = malloc(matrix_w * matrix_h);

 /* if (screen_matrix == NULL)
  {
	printf("echec allocation memoire");
	exit(0);
  }*/

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
			if(force_exit == 1)
			{
				break;
			}
		}
		
		if(force_exit == 1)
		{
			screen_matrix[i + j * divisor] = 1;
		//	break;


			//coloration jaune hardcodee 
			
										
		for(unsigned k = i * matrix_w; k < upper_limit_w; k++)
		{
			for(unsigned l = j * matrix_h; l < upper_limit_h; l++)
			{
				putpixel(screen, k, l, pixel);
				//printf("pixel_put");
			}
		}


		}
		else
		{
			screen_matrix[i + j * divisor] = 0;
		}
	} 
  }
}

void __block_merging( char screen_matrix[], size_t w, size_t h, size_t i, size_t j,size_t* xmin, size_t* xmax, size_t* ymin, size_t* ymax)
{
    *xmin = i < *xmin ? i : *xmin;
    *xmax = i > *xmax ? i : *xmax;
    *ymin = j < *ymin ? j : *ymin;
    *ymax = j > *ymax ? j : *ymax;
        
    if(screen_matrix[i +j * w]== 1){screen_matrix[i + j * w] = 2;}

    if ( j > 0 && screen_matrix[i +(j-1) * w] == 1)
    {   
        __block_merging( screen_matrix, w, h, i, j-1, xmin, xmax, ymin, ymax);
    }

    if( j < h-1 && screen_matrix[i +(j+1) *w] == 1)
    {
        __block_merging( screen_matrix, w, h, i, j+1, xmin, xmax, ymin, ymax);
    }
    
    if( i > 0 && screen_matrix[(i-1) + j * w] == 1)
    {
        __block_merging( screen_matrix, w, h, i-1, j, xmin, xmax, ymin, ymax);
    }
    
    if( i < w-1 && screen_matrix[(i+1) + j* w] == 1)
    {
        __block_merging( screen_matrix, w, h, i+1, j, xmin, xmax, ymin, ymax);
    }

           
} 

size_t  block_merging(char screen_matrix[], size_t w, size_t h, size_t tab[])
{
    printf("appel de bloc merging ");
    size_t len = 0;
    size_t xmin = 0;
    size_t xmax = 0;
    size_t ymin = 0;
    size_t ymax = 0;
    
    size_t mult = 0;

//	char screen_matrix_copy[w * h];
	for(size_t i = 0; i < w; i++)
	{
		for(size_t j = 0; j < h; j++)
		{
			if (screen_matrix[i + j * w] == 1)
            {
                __block_merging( screen_matrix, w, h, i, j, &xmin,&xmax,&ymin,&ymax);

                tab[mult*4] = xmin;
                tab[mult*4 +1] = xmax;
                tab[mult*4 +2] = ymin;
                tab[mult*4 +3] = ymax;
                len += 4;
                xmin = 0;
                xmax = 0;
                ymin = 0;
                ymax = 0;
            }			 
		}
	}
    
    //free(screen_matrix);

    return len;
}

void block_colorizing(SDL_Surface* screen, char screen_matrix[], char divisor)
{
    Uint32 pixel = SDL_MapRGB(screen->format, 0, 150,150);
    size_t w = screen->w;
    size_t h = screen->h;

    size_t matrix_w = w / divisor;
    size_t matrix_h = h / divisor;

    for (char i = 0; i < divisor; i++)
    {
        for(char j = 0; j < divisor; j++)
        {
            unsigned upper_limit_w = i == divisor-1 ? w : (i + 1) * matrix_w; //gestion derniere case : plus grande que les autres.
            unsigned upper_limit_h = j == divisor-1 ? h : (j + 1) * matrix_h;

            for(unsigned k = i * matrix_w; k < upper_limit_w; k++)
            {
                for(unsigned l = j * matrix_h; l < upper_limit_h; l++)
                {
        

            if(screen_matrix[i + j* matrix_w] == 2)
            {
                //on colorie
                for(unsigned k = i * matrix_w; k < upper_limit_w; k++)
                {
                    for(unsigned l = j * matrix_h; l < upper_limit_h; l++)
                    {
                        putpixel(screen, k, l, pixel);
                        //printf("pixel_put");
                    }
                }


            }
     }
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



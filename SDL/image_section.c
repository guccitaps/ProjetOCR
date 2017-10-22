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
    //*xmin = i < *xmin ? i : *xmin; // La fameuse forme ternaire sur laquelle j'ai un doute vu les valeurs rendues par tab
    //*xmax = i > *xmax ? i : *xmax;
    //*ymin = j < *ymin ? j : *ymin;
    //*ymax = j > *ymax ? j : *ymax;
        
    //printf(" xmax = %zu, pointeur = %p \n", *xmax, xmax);


    if(screen_matrix[i +j * w]== 1)
    {
	*xmin = i < *xmin ? i : *xmin; // La fameuse forme ternaire sur laquelle j'ai un doute vu les valeurs rendues par tab
        *xmax = i > *xmax ? i : *xmax;
        *ymin = j < *ymin ? j : *ymin;
        *ymax = j > *ymax ? j : *ymax;

	
	screen_matrix[i + j * w] = 2;
    } 													// Je vérifie une seconde fois si le bloc contient bien des char, au cas ou je fais un mauvais appel
								   //								et je mets sa valeur à 2 pour ne pas relancer dessus
    if ( j > 0 && screen_matrix[i +(j-1) * w] == 1) // Je regarde si le block au dessus contient des char
    {   
        __block_merging( screen_matrix, w, h, i, j-1, xmin, xmax, ymin, ymax); // Appel récursif
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
    //printf("appel de bloc merging ");
    size_t len = 0;
    size_t xmin = 1000; // Je définis ces variables comme des size_t
    size_t xmax = 0;
    size_t ymin = 1000;
    size_t ymax = 0;
    
    size_t mult = 0;

//	char screen_matrix_copy[w * h];
	for(size_t i = 0; i < w; i++)
	{
		for(size_t j = 0; j < h; j++)
		{
			if (screen_matrix[i + j * w] == 1) // Si le bloc contient des charactères
            {
                __block_merging( screen_matrix, w, h, i, j, &xmin,&xmax,&ymin,&ymax); // Je récupère les pointeurs sur les adresses de mes variables avec &
										      // Ca me permet d'initialiser la valeurs de ces pointeurs

                tab[mult*4] = xmin; // Tab est une matrice à une dimension de taille 100
                tab[mult*4 +1] = xmax;
                tab[mult*4 +2] = ymin;
                tab[mult*4 +3] = ymax;
		printf(" xmax = %zu, pointeur = %p, tab =%zu \n", xmax, &xmax, tab[mult*4+1]);
                len += 4; // Len qui nous permet de connaitre le nombre de bloc détecté
                xmin = 1000; // Je remets toutes les variables à 0 pour les prochaines comparaisons
                xmax = 0;
                ymin = 1000;
                ymax = 0;
		mult++;
            }			 
		}
	}
    
    //free(screen_matrix);

    return len;
}

void block_colorizing(SDL_Surface* screen, size_t divisor, size_t tab[], size_t len)
{
    Uint32 pixel = SDL_MapRGB(screen->format, 0, 150,150);
    size_t w = screen->w;
    size_t h = screen->h;

    size_t matrix_w = w / divisor;
    size_t matrix_h = h / divisor;
    for( size_t n = 0; n < len; n += 4) // Pour chaque bloc de texte
    {
    	for (size_t i = tab[n]; i <= tab[n+1]; i++) // Pour chaque " case " allant de xmin a xmax
    	{
        	for(size_t j = tab[n+2]; j <= tab[n+3]; j++)
        	{
            		unsigned upper_limit_w = i == divisor-1 ? w : (i + 1) * matrix_w; //gestion derniere case : plus grande que les autres.
            		unsigned upper_limit_h = j == divisor-1 ? h : (j + 1) * matrix_h;
                			//on colorie
                	for(unsigned k = i * matrix_w; k < upper_limit_w; k++) // Pour chaque pixel de la case
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



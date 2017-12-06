#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <gtk/gtk.h>
#include <err.h>
#include "pixel_operations.h"
#include "image_section.h"
//#include "charcut.h"

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
 // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}

void print_matrix(char mat[], size_t lines, size_t cols)
{	
	for(unsigned i = 0; i < lines; i++)
	{
		for(unsigned j = 0; j < cols; j++)
		{
			printf("%d    ",mat[j + i * cols]);
		}
	  printf("\n");
	}
}
int main(int argc, char *argv[])
{
  
if (argc < 2 && argc > 3)
  {  
	printf("nop");
	return -1;
  }
  else
  {
    int arg = atoi(argv[2]);
    printf("%d",arg);
	init_sdl();
	SDL_Surface* image = load_image(argv[1]); 
	forall_func(image, greyconvert);
	SDL_Surface* screen = display_image(image);
	forall_func(image, black_or_white);
    SDL_Surface* image2 = load_image(argv[1]);
    forall_func(image2, greyconvert);
    forall_func(image2, black_or_white);
	screen = display_image(image);
	
	/*char mat[arg * arg];
	bloc_detection(image, mat, arg);	
	print_matrix(mat, arg, arg);
	screen = display_image(image);
    size_t tab[10000];
    printf("appel primaire");
    size_t len = block_merging(image, mat, arg, arg, tab);
    bloc_colorizing(image, tab, len);
    screen = display_image(image);
    size_t charlist[50000];
    size_t lenresult = cutimage(charlist, tab, len, image2);
    char_colorizing(image2, charlist, lenresult); // mettre charlist image2 lenresult
    screen = display_image(image2); // mettre image2
    print_matrix(mat, arg, arg);
	SDL_FreeSurface(screen);
    printf("len = %zu \n", lenresult);
	return 0; */
    
    SDL_Surface* image3 = SDL_CreateRGBSurface(0,200,200,32,0,0,0,0);
    SDL_BlitSurface( image, NULL, image3, NULL);
    screen = display_image(image3);
    return 0;
    
  }
}

// pixel_operations.c
 
// Simple get/put pixel for SDL
// Inspired by code from SDL documentation
// (http://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html)
 
# include "pixel_operations.h"
# include <math.h>
 
static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}

Uint32 black_or_white(Uint32 pixel, SDL_Surface* screen)
{
  Uint8 r = 8;
  
  SDL_GetRGB(pixel, screen->format, &r, &r, &r);

  r = r > 127 ? 255 : 0;

  return SDL_MapRGB(screen->format, r, r, r);
}



Uint32 greyconvert(Uint32 pixel, SDL_Surface* screen)
{
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;

  SDL_GetRGB(pixel, screen->format, &r, &g, &b);
  Uint8  avg = r * 0.3 + g * 0.59 + b * 0.11;
  return SDL_MapRGB(screen->format, avg, avg, avg);
}


void forall_func(SDL_Surface* screen, func_t f)
{
  unsigned w = 0;
  unsigned h = 0;
  w = screen->w;
  h = screen->h;
  for(unsigned i = 0; i < w; i++)
  {
	for(unsigned j = 0; j < h; j++)
	{
		Uint32 pixel = f(getpixel(screen, i, j), screen);
		putpixel(screen, i, j, pixel);
	}
  }
}




void sobel_filter(SDL_Surface* screen, SDL_Surface* screen2, _Bool x, _Bool y)  //horizontal filter
{	
  int weight_x[3][3] ={ {	-1,	0,	1},
	      		{	-2,	0,	2},
			{	-1,	0,	1}};

  int weight_y[3][3] ={ {	-1,	-2,	-1},
			{  	 0,	 0,	 0},
			{	 1,	 2,	 1}};

  const SDL_PixelFormat* pixel_format = screen->format;
  Uint8 r;
  Uint8 g;
  Uint8 b;

  double pixel_red_value_x = 0;
  double pixel_red_value_y = 0;
  Uint32 current_pixel_value = 0;  

  unsigned w = screen->w;
  unsigned h = screen->h;
  for(unsigned i = 0; i < w; i++)
  {
	for(unsigned j = 0; j < h; j++)
	{
		pixel_red_value_x = 0;
		pixel_red_value_y = 0;
		for (int x = -1; x < 2; x++)
		{
			for(int y = -1; y < 2; y++)
			{	
				if (i+x < w && j+y < h)
				{
					current_pixel_value = getpixel(screen, i+x, j+y);
					SDL_GetRGB(current_pixel_value, pixel_format, &r, &g, &b);
					pixel_red_value_x += weight_x[x + 1][y + 1] * r;
					pixel_red_value_y += weight_y[x + 1][y + 1] * r;
				}
			}
		}
	//	printf("%f", pixel_red_value);
		Uint8 formated_red_value = 0;
		if (pixel_red_value_x > 255)
		{
			pixel_red_value_x = 255;
		}
		else if (pixel_red_value_x < 0)
		{
			pixel_red_value_x = 0;
		}
		
		if (pixel_red_value_y > 255)
		{
			pixel_red_value_y = 255;
		}
		else if (pixel_red_value_y < 0)
		{
			pixel_red_value_y = 0;
		}
		if (!x)
			pixel_red_value_x = 0;
		if (!y)
			pixel_red_value_y = 0;
		formated_red_value = sqrt(pixel_red_value_x * pixel_red_value_x + pixel_red_value_y * pixel_red_value_y);
//		formated_red_value = pixel_red_value_x;
		//pixel_red_value = 255 * (pixel_red_value - min) / (max - min);
		Uint32 pixel = SDL_MapRGB(pixel_format, formated_red_value, formated_red_value, formated_red_value);
		putpixel(screen2, i, j, pixel);

	}
  }


}











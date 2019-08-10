
#include "SDL.h"
#include <iostream>
#include <math.h>

using namespace std;

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
  *(Uint32 *)target_pixel = pixel;
}

int main( int argc, char* argv[] )
{
  /* setup planet and ship initial */
  float speedMod = 0.1;
  float planetX = 300, planetY = 300, planetR = 50, planetG = 10000 * speedMod;
  //  float planetX2 = 300, planetY2 = 100, planetR2 = 50, planetG2 = 10000 * speedMod;
  float shipX = 300, shipY = 200;
  float vX = 10, vY = 0;
  float dist = 100;
  
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("Orbit Test", "Orbit Test");

  /* create window */
  SDL_Surface* screen = SDL_SetVideoMode(600, 600, 0, 0);

  /* load bitmap to temp surface */
  SDL_Surface* temp = SDL_LoadBMP("planet.bmp");

  /* convert bitmap to display format */
  SDL_Surface* bg = SDL_DisplayFormat(temp);

  /* free the temp surface */
  SDL_FreeSurface(temp);

  SDL_Event event;
  int gameover = 0;
  
  /* message pump */
  while (!gameover)
    {
      /* look for an event */
      if (SDL_PollEvent(&event)) {
		  
	/* an event was found */
	switch (event.type) {
	  /* close button clicked */
	case SDL_QUIT:
	  gameover = 1;
	  break;

	  /* handle the keyboard */
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	  case SDLK_q:
	    //gameover = 1;
	    break;

	    /* increase speed */
	  case SDLK_w:
	    vX += 1*(shipX-planetX)/dist;
	    vY += 1*(shipX-planetX)/dist;
	    break;
	    /* decrease speed */
	  case SDLK_s:
	    vX -= 1*(shipX-planetX)/dist;
	    vY -= 1*(shipX-planetX)/dist;
	    break;
	  }
	  break;
	}
      }

      /* draw ship */
      if (shipY > 0 && shipY < 600){
	set_pixel(bg, int(shipX), int(shipY), 0xFFFFFF);
      }
      /* simulates gravity */
      dist = sqrt((shipX-planetX)*(shipX-planetX)+(shipY-planetY)*(shipY-planetY));
      vX -= (shipX-planetX)*planetG/(dist*dist*dist);
      vY -= (shipY-planetY)*planetG/(dist*dist*dist);
      //   int dist2 = sqrt((shipX-planetX2)*(shipX-planetX2)+(shipY-planetY2)*(shipY-planetY2));
      //vX -= (shipX-planetX)*planetG2/(dist2*dist2*dist2);
      //vY -= (shipY-planetY2)*planetG2/(dist2*dist2*dist2);
      
      /* update ship position */
      shipX = vX*speedMod + shipX;
      shipY = vY*speedMod + shipY;

      /* wall bounce */
      /*
      if (shipX < 0 || shipX >= 600){
	shipX -= 2*vX*speedMod;
	vX = -vX;
      }
      else if (shipY < 0 || shipY >= 600){
	shipY -= 2*vY*speedMod;
	vY = -vY;
      }
      */

      /* draw the screen */
      SDL_BlitSurface(bg, NULL, screen, NULL);
      
      /* update the screen */
      SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
  cout << "exit" << endl;

  /* free the background surface */
  SDL_FreeSurface(bg);

  /* cleanup SDL */
  SDL_Quit();

  return 0;
}


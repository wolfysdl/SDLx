#include <SDL.h>
#include <SDL_mixer.h>

#define WIDTH 640
#define HEIGHT 480
#define BITS 32

typedef enum
{
  false,
  true
}bool;

int main(int args, char *argv[])
{
	SDL_Surface *screen;
	SDL_Surface *chalice;
	Mix_Music *chalice_mus;

	SDL_Init(SDL_INIT_EVERYTHING);

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	  return 0;

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BITS, SDL_SWSURFACE);

	chalice = SDL_LoadBMP("Calice.bmp");

	chalice_mus = Mix_LoadMUS("Calice.wav");

	SDL_BlitSurface(chalice, NULL, screen, NULL);

	SDL_Flip(screen);

	SDL_Delay(300000);

	SDL_FreeSurface(chalice);

	SDL_Quit();

}
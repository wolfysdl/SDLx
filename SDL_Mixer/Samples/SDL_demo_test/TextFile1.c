#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "SDL_mixer.h"

Mix_Chunk *phaser = NULL;
Mix_Music *music = NULL;

int phaserChannel = -1;

void handleKey(SDL_KeyboardEvent key);
void musicDone();

int main(void) {

  SDL_Surface *screen;
  SDL_Event event;
  int done = 0;

  /* Same setup as before */
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16; 
  int audio_channels = 2;
  int audio_buffers = 4096;

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Unable to open audio!\n");
    exit(1);
  }

  /* Pre-load sound effects */
  phaser = Mix_LoadWAV("phaser.wav");

  screen = SDL_SetVideoMode(320, 240, 0, 0);

  while(!done) {
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_QUIT:
	done = 1;
	break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
	handleKey(event.key);
	break;
      }
    }
    SDL_Delay(50);

  }

  Mix_CloseAudio();
  SDL_Quit();

}

void handleKey(SDL_KeyboardEvent key) {
  switch(key.keysym.sym) {
  case SDLK_p:

    if(key.type == SDL_KEYDOWN) {

      if(phaserChannel < 0) {
	phaserChannel = Mix_PlayChannel(-1, phaser, -1);
      }
    } else {
      Mix_HaltChannel(phaserChannel);
      
      phaserChannel = -1;
    }
    break;
  case SDLK_m:
    if(key.state == SDL_PRESSED) {

      if(music == NULL) {
	
	music = Mix_LoadMUS("music.ogg");
	Mix_PlayMusic(music, 0);
	Mix_HookMusicFinished(musicDone);
	
      } else {
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = NULL;
      }
    }
    break;
  }
}

void musicDone() {
  Mix_HaltMusic();
  Mix_FreeMusic(music);
  music = NULL;
}

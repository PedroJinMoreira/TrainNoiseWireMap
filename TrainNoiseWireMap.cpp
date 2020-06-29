#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_opengl.h>

using namespace std;
SDL_Window* wndw= NULL;
SDL_Event evnt;
SDL_GLContext glc;
int run=1;
int _WDHT=1080;
int _HGHT=720;
int argc; char **argv;

#include <main.cpp>
int main(int c, char **v){
	argc=c;
	argv=v;
	//InitSDL
	if(SDL_Init(SDL_INIT_EVERYTHING)){
		printf("SDL2 init ERROR\n%s", SDL_GetError());
		return 1;
	}
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32 );
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );
	
	// Create window
	wndw = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if(wndw == NULL){
		printf("Creating Windows ERROR\n%s", SDL_GetError());
		return 1;
	}

	//Create gl context
	glc = SDL_GL_CreateContext(wndw);
	if(!glc){
		printf("Creating OGL context ERROR\n%s", SDL_GetError());
		return 1;
	}

	start();
	// Game loop
	while (run){
		while(SDL_PollEvent(&evnt) != 0){
			if(evnt.type == SDL_KEYDOWN ) {
				if(evnt.key.keysym.sym == SDLK_ESCAPE) run = 0;

			}
			if(evnt.type==SDL_WINDOWEVENT){
				if(evnt.window.event){
					SDL_GetWindowSize(wndw, &_WDHT, &_HGHT);
					glViewport(0, 0, _WDHT, _HGHT);
				}
			}
		}
		update();
		SDL_GL_SwapWindow(wndw);
	}
	SDL_DestroyWindow(wndw);
	exit();
	return 0;
}

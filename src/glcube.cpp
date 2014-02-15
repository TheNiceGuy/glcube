/////////////////////////////////////////////////////////////////////////
//                                                                     //
//  glcube.cpp                                                         //
//                                                                     //
//  Copyright (c) 2013-2014 Gabriel-Andrew Pollo Guilbert              //
//                          <gabriel14_wii@hotmail.com>                //
//                                                                     //
//                        All Rights Reserved                          //
//                                                                     //
//  This program is free software. It comes without  any warranty, to  //
//  the extent permitted by  applicable law. You can  redistribute it  //
//  and/or modify it under the terms of the Do What the Fuck You Want  //
//  to  Public  License, Version 2, as  published by Sam Hocevar. See  //
//  http://www.wtfpl.net/ for more details.                            //
//                                                                     //
/////////////////////////////////////////////////////////////////////////  

#include "camera.h"
#include "cube.h"
#include "render.h"
#include "global.h"

using namespace std;

int             resolution_x    = 800;
int             resolution_y    = 600;
bool            render_thread   = false;
pthread_t       render_pthread;
pthread_mutex_t render_mutex    = PTHREAD_MUTEX_INITIALIZER;
cube            cube;
camera          camera;

void init();
void render();

int main()
{
	bool sdl_exit = false;
	SDL_Event event;
	SDL_version compiled;
	SDL_version linked;
	
	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	
	printf("SDL compiled version: %d.%d.%d\n", compiled.major, compiled.minor, compiled.patch);
	printf("SDL linked version: %d.%d.%d\n", linked.major, linked.minor, linked.patch);

 	init();
	while (sdl_exit != true)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				sdl_exit = true;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						sdl_exit = true;
						break;
					case SDLK_f:
						window_fullscreen();
						break;
					case SDLK_g:
						toggle_grid();
						break;
					case SDLK_HOME:
						camera.reset_camera();
						break;
					case SDLK_PAGEUP:
						cube.layer_up();
						break;
					case SDLK_PAGEDOWN:
						cube.layer_down();
						break;
				}	
				break;
			
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button)
				{
					case SDL_BUTTON_MIDDLE:
						camera.mouse_button(event.button);
						break;
				}
				break;
				
			case SDL_MOUSEMOTION:
				camera.mouse_motion(event.motion);
				break;
				
			case SDL_MOUSEWHEEL:
				camera.mouse_wheel(event.wheel);
				break;
				
			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						window_resize_event(event.window);
						break;
				}
				break;
		}
	}
	render_thread = false;
	pthread_join(render_pthread, NULL);
	SDL_Quit();
	return 0;
}

void init()
{	
	pthread_create(&render_pthread, NULL, &startTimer, NULL);
	sleep(1);
	
	pthread_mutex_lock(&render_mutex);
	pthread_mutex_unlock(&render_mutex);
}
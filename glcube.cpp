#include "camera.h"
#include "cube.h"
#include "render.h"
#include "global.h"

using namespace std;

cube            cube;
camera          camera;
bool            render_thread   = false;
pthread_t       render_pthread;
pthread_mutex_t render_mutex    = PTHREAD_MUTEX_INITIALIZER;

void init();
void render();

int main()
{
	bool sdl_exit = false;
	SDL_Event event;

 	init();
	while (sdl_exit != true)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				sdl_exit = true;
				break;

			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				camera.mouse_button(event.button);
				break;

			case SDL_MOUSEMOTION:
				camera.mouse_motion(event.motion);
				break;
				
			case SDL_MOUSEWHEEL:
				camera.mouse_wheel(event.wheel);
		}
	}
	render_thread = false;
	pthread_join(render_pthread, NULL);
	SDL_Quit();
	return 0;
}

void init()
{	
	cube.generate();
	
	pthread_create(&render_pthread, NULL, &startTimer, NULL);
	sleep(1);
	
	pthread_mutex_lock(&render_mutex);
	pthread_mutex_unlock(&render_mutex);
}









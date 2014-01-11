#include "render.h"

using namespace std;

extern cube            cube;
extern camera          camera;
extern bool            render_thread;
extern pthread_mutex_t render_mutex;

SDL_Window *screen;

void *startTimer(void*)
{
	int time       = 0;
	int time_delay = 0;
	render_thread  = true;
	
	pthread_mutex_lock(&render_mutex);
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("Unable to initialize SDL: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_CreateWindow("GLCube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  640, 640, SDL_WINDOW_OPENGL);
	if(screen == NULL)
	{
		printf("Can't create SDL window: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_GL_CreateContext(screen);
	glEnable(GL_DEPTH_TEST);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	pthread_mutex_unlock(&render_mutex);
	
	render();

	while(render_thread == true)
	{
		time = SDL_GetTicks();
		if(time - time_delay > (1000/60))
		{
			pthread_mutex_lock(&render_mutex);
			render();
			pthread_mutex_unlock(&render_mutex);
			time_delay = time;
		}
	}
	
	return NULL;
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.39, 0.88, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(60.0, 1, 0.5, 40.0);

	camera.move_camera();	
	cube.draw();
	
	glFlush();
	SDL_GL_SwapWindow(screen);	
}

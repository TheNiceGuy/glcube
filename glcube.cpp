#include "cube.h"
#include "camera.h"
#include "render.h"
#include "global.h"

using namespace std;

cube cube;
camera camera;
bool render_thread = false;

void init();
void render();

int main()
{
	startTimer(17);

	bool sdl_exit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
 	SDL_WM_SetCaption("GLCube", NULL);
	SDL_SetVideoMode(480, 480, 32, SDL_OPENGL); 

 	init();
	render();
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
				camera.mouseButton(event.button);
				break;

			case SDL_MOUSEMOTION:
				camera.mouseMotion(event.motion);
				break;
		}
		render();
	}
 
	SDL_Quit();
	return 0;
}

void init()
{	
	cube.generate();
	cube.rotate(0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.8, 0.8, 1);
	gluPerspective(70, 1, 1, 1000);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);

	cube.draw();

	glFlush();
	SDL_GL_SwapBuffers();	
}









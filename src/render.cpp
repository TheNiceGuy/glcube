#include "render.h"

using namespace std;

extern int             resolution_x;
extern int             resolution_y;
extern bool            render_thread;
extern pthread_mutex_t render_mutex;
extern cube            cube;
extern camera          camera;

SDL_Window *window;
SDL_GLContext window_glcontext;
bool render_grid = true;

void render_init()
{
	pthread_mutex_lock(&render_mutex);
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("Unable to initialize SDL: %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	window = SDL_CreateWindow("GLCube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  resolution_x, resolution_y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if(window == NULL)
	{
		printf("Can't create SDL window: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	window_glcontext = SDL_GL_CreateContext(window);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	pthread_mutex_unlock(&render_mutex);
	
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	
	if(TTF_Init() == -1)
	{
		printf("Can't initialize TTF: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
}
void *startTimer(void*)
{
	int time       = 0;
	int time_delay = 0;
	render_thread  = true;
	
	render_init();
float a[16]; 
glGetFloatv(GL_MODELVIEW_MATRIX, a);

cout << a[ 0] << "	" << a[ 1] << "	" << a[ 2] << "	" << a[ 3] << endl;
cout << a[ 4] << "	" << a[ 5] << "	" << a[ 6] << "	" << a[ 7] << endl;
cout << a[ 8] << "	" << a[ 9] << "	" << a[10] << "	" << a[11] << endl;
cout << a[12] << "	" << a[13] << "	" << a[14] << "	" << a[15] << endl;

	window_resize(resolution_x, resolution_y);
	window_render();
	
glLoadIdentity();

	while(render_thread == true)
	{
		time = SDL_GetTicks();
		if(time - time_delay > (1000/60))
		{
			pthread_mutex_lock(&render_mutex);
			window_render();
			pthread_mutex_unlock(&render_mutex);
			time_delay = time;
		}
	}
	SDL_GL_DeleteContext(window_glcontext);
	SDL_DestroyWindow(window);
	return NULL;
}

void window_resize(int x, int y)
{
	GLfloat ratio;
	
	if(y == 0)
		y = 1;
	ratio = (GLfloat)x/(GLfloat)y;
	
	glViewport(0, 0, (GLsizei)x, (GLsizei)y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void window_render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1, 0.39, 0.88, 1.0);
	glLoadIdentity();

	window_resize(resolution_x, resolution_y);

	camera.move_camera();
	if(render_grid == true)
		draw_grid(20, 1);
	if(cube.is_lock() == false)
		cube.draw();
	//font_render();
	
	float x[4], y[4], z[4];

	glFlush();
	SDL_GL_SwapWindow(window);	
}

void window_resize_event(const SDL_WindowEvent &event)
{
	resolution_x = event.data1;
	resolution_y = event.data2;
}

void window_fullscreen()
{
	static int old_x, old_y;
	int x, y;
	int temp_x, temp_y;
	Uint32 flags = SDL_GetWindowFlags(window);
	SDL_DisplayMode current;
	
	temp_x = resolution_x;
	temp_y = resolution_y;
	
	for(int i = 0; i<SDL_GetNumVideoDisplays(); ++i)
	{
		int a = SDL_GetCurrentDisplayMode(i, &current);
		if(a != 0)
			printf("Could not get display mode for video display #%d: %s\n", i, SDL_GetError());
		else
			x = current.w;
			y = current.h;
	}
	
	if(flags & SDL_WINDOW_FULLSCREEN)
	{
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		SDL_SetWindowSize(window, old_x, old_y);
	}
	else
	{
		SDL_SetWindowSize(window, x, y);
		SDL_SetWindowFullscreen(window, SDL_TRUE);
	}
	
	old_x = temp_x;
	old_y = temp_y;
}
/*
void font_render()
{
	SDL_Surface *font_surface;
	SDL_Texture *font_texture;
	SDL_Color    color;
	TTF_Font    *font;
	GLuint       texture_id;
	GLuint       shader_program_text;
	
	color = {255, 0, 0, 0};
	font = TTF_OpenFont("font/UbuntuMono-R.ttf", 50);	

	font_surface = TTF_RenderText_Blended(font, "Hello World", color);

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, font_surface->w, font_surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, font_surface->pixels);
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(font_surface);
	TTF_CloseFont(font);
}
*/

void draw_grid(int n, float s)
{
	glPushMatrix();
	//glTranslatef(0.5, 0.5, 0.5);
	for(int x = 0; x<n+1; x++)
	{
		glBegin(GL_LINES);
			glColor3ub(0, 0, 255);
			glVertex3f( x*s, 0, n*s);
			glVertex3f( x*s, 0,-n*s);
			glVertex3f(-x*s, 0, n*s);
			glVertex3f(-x*s, 0,-n*s);
			glColor3ub(255, 0, 0);
			glVertex3f( n*s, 0, x*s);
			glVertex3f(-n*s, 0, x*s);
			glVertex3f( n*s, 0,-x*s);
			glVertex3f(-n*s, 0,-x*s);
		glEnd();
	}
	glPopMatrix();
}

void toggle_grid()
{
	if(render_grid == true)
		render_grid = false;
	else
		render_grid = true;
}
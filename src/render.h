#ifndef RENDER_H
#define RENDER_H

#include "camera.h"
#include "cube.h"
#include "global.h"

void render_init();
void *startTimer(void*);
void window_render();
void window_resize(int x, int y);
void window_resize_event(const SDL_WindowEvent &event);
void window_fullscreen();
void get_display();
void font_render();
void draw_grid(int n, float s);
void toggle_grid();

#endif
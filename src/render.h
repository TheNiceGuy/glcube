/*
 * render.h
 *
 * Copyright (c) 2013-2014 Gabriel-Andrew Pollo Guilbert
 *                         <gabriel14_wii@hotmail.com>
 *
 *                       All Rights Reserved
 *
 * This program is free software. It comes without  any warranty, to
 * the extent permitted by  applicable law. You can  redistribute it
 * and/or modify it under the terms of the Do What the Fuck You Want
 * to  Public  License, Version 2, as  published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

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

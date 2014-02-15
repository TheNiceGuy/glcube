/////////////////////////////////////////////////////////////////////////
//                                                                     //
//  camera.h                                                           //
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

#ifndef CAMERA_H
#define CAMERA_H
#define _USE_MATH_DEFINES

#include <cmath>

#include "global.h"


inline float degToRad(float x)
{
    return x / 180 * M_PI;
}

class camera
{
	public:
		camera();
 
		uint16_t mouse_motion(const SDL_MouseMotionEvent &event);
		uint16_t mouse_button(const SDL_MouseButtonEvent &event);
		uint16_t mouse_wheel(const SDL_MouseWheelEvent &event);
		uint16_t keyboard_input(const SDL_KeyboardEvent &event); 
		uint16_t set_camera();
		uint16_t set_motion_sensitity(double sens);
		uint16_t set_scroll_sensitity(double sens);
		uint16_t move_camera();
		uint16_t reset_camera();
		
		~camera();

	private:
		int distance_min;
		int distance_max;
		double distance;
		double mouse_speed;
		double scroll_speed;
		double angle[2];
		double pos[2];
		bool flip_rotation;
		bool left_button;
		bool right_button;
		
		uint16_t update_pos();
};

#endif
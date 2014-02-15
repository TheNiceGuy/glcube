/////////////////////////////////////////////////////////////////////////
//                                                                     //
//  camera.cpp                                                         //
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

using namespace std;

uint16_t camera::mouse_motion(const SDL_MouseMotionEvent &event)
{
	if(left_button == true)
	{	
		if(flip_rotation == false)
			angle[0] = angle[0] + (event.xrel * mouse_speed);
		else
			angle[0] = angle[0] - (event.xrel * mouse_speed);
		angle[1] = angle[1] + (event.yrel * mouse_speed);
		for(int i = 0; i < 2; i++)
		{
			if(angle[i] >= 360)
				angle[i] = angle[i] - 360;
			else if(angle[i] <= -360)
				angle[i] = angle[i] + 360;
		}
	}
	return 0;
}

uint16_t camera::mouse_button(const SDL_MouseButtonEvent &event)
{
	if(event.state == SDL_PRESSED)
	{
		left_button = true;	
	}
	else
	{
		left_button = false;
		if( (angle[1]> 90 and angle[1]< 270) or
			(angle[1]<-90 and angle[1]>-270) )
			flip_rotation = true;
		else
			flip_rotation = false;
	}
	return 0;
}

uint16_t camera::mouse_wheel(const SDL_MouseWheelEvent &event)
{
	double i;	
	i = distance - (event.y * scroll_speed);
	
	if(i<distance_min)
		distance = distance_min;
	else if(i>distance_max)
		distance = distance_max;
	else
		distance = i;
	
	return 0;
}

uint16_t camera::move_camera()
{
	update_pos();
	
	if((angle[1] <=  90 and angle[1] >=  -90) or
		angle[1] >  270  or angle[1] <  -270)
		gluLookAt(pos[0], pos[1], 0, 0, 0, 0, 0, 1, 0);	
	else
		gluLookAt(pos[0], pos[1], 0, 0, 0, 0, 0,-1, 0);
	
	glRotated(angle[0], 0, 1, 0);
	
	return 0;
}

uint16_t camera::reset_camera()
{
	angle[0] = 45;
	angle[1] = 45;
	distance = distance_min;
	
	return 0;
}

//////////////////////
// private function //
//////////////////////

camera::camera()
{
	distance_min  = 10;
	distance_max  = 50;
	distance      = distance_min;
	mouse_speed   = 0.4;
	scroll_speed  = 1;
	flip_rotation = false;
	left_button   = false;
	right_button  = false;
	for(int i = 0; i<2; i++)
	{
		angle[i] = 45;
		pos[i]   = 0;
	}
}

uint16_t camera::update_pos()
{
		pos[0] = distance * cos(angle[1]*M_PI/180);
		pos[1] = distance * sin(angle[1]*M_PI/180);
		
		return 0;
}

camera::~camera()
{
	
}
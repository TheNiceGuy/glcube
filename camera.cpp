#include "camera.h"

using namespace std;

uint16_t camera::mouse_motion(const SDL_MouseMotionEvent &event)
{
	if(left_button == true)
	{	
		angle[1] = angle[1] + event.yrel;
		for(int i = 0; i < 2; i++)
		{
			if(angle[i] >= 360)
				angle[i] = angle[i] - 360;
			else if(angle[i] <= -360)
				angle[i] = angle[i] + 360;
		}
		if(flip_rotation == false)
			angle[0] = angle[0] + event.xrel;
		else
			angle[0] = angle[0] - event.xrel;
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

//////////////////////
// private function //
//////////////////////

camera::camera()
{
	distance      = distance_min;
	mouse_speed   = 0.3;
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
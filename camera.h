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
		
		~camera();

	private:
		double distance;
		double mouse_speed;
		double scroll_speed;
		double angle[2];
		double pos[2];
		bool left_button;
		bool right_button;
		
		uint16_t update_pos();
};

#endif

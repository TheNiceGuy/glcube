#ifndef CAMERA_H
#define CAMERA_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <unistd.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

inline float degToRad(float x)
{
    return x / 180 * M_PI;
}

class camera
{
	public:
		camera();
 
		uint16_t mouseMotion(const SDL_MouseMotionEvent &event);
		uint16_t mouseButton(const SDL_MouseButtonEvent &event);
		uint16_t keyboardInput(const SDL_KeyboardEvent &event); 
		uint16_t setCamera();
		uint16_t setMotionSensivity(double sensivity);
		uint16_t setScrollSensivity(double sensivity);

		~camera();

	private:
		double MouseSpeed;
		double ScrollSpeed;
		double Distance;
		double AngleY;
		double AngleZ;
		bool LeftButton;
		bool RightButton;
};

#endif

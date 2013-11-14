#include "camera.h"
#include "global.h"

using namespace std;

camera::camera()
{
	MouseSpeed  = 0.3;
	ScrollSpeed = 1;
	Distance    = 10;
	AngleY      = 0;
	AngleZ      = 0;
	LeftButton  = false;
	RightButton = false;
}

uint16_t camera::mouseMotion(const SDL_MouseMotionEvent &event)
{
	if(LeftButton == true)
	{
		cout << event.xrel << " " << event.yrel << endl;
	}
	return 0;
}

uint16_t camera::mouseButton(const SDL_MouseButtonEvent &event)
{
	if(event.state == SDL_PRESSED)
	{
		LeftButton = true;	
	}
	else
	{
		LeftButton = false;
	}
	return 0;
}

camera::~camera()
{
	
}

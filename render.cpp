#include "render.h"
#include "global.h"

void startTimer(int interval)
{
	cout << "start timer" << endl;
	usleep(interval);
	cout << "after timer" << endl;
}

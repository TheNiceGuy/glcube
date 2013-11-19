#include "render.h"
#include "global.h"

using namespace std;

extern bool render_thread;

void startTimer(int interval)
{
	render_thread = true;

	while(render_thread == true)
	{
		cout << "such timer" << endl;
		sleep(interval);
	}
}

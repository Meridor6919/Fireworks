#include "Game.h"
#include <time.h>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instace, LPSTR cmd_line, int show_cmd)
{
	srand(static_cast<unsigned int>(time(NULL)));//change to diffrent rand func
	Game xd(instance);
	if (xd.Init())
	{
		xd.Run();
	}
}
#include "GLWindow.h"
#include "Render.h"
#include "Timer.h"

GLWindow win;
Timer timer;
float frametime=0;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	float framestart;

	win.Create("Map Creator",hInstance,1024,768,16);
	timer.Init();

	if(!Init())
	{
		win.Message("Error: Init");
		win.quit=true;
	}

	while(!win.quit)
	{
		framestart=timer.GetTime();

		win.DamnedMessages();

		if(win.key[VK_ESCAPE])
			win.quit=true;

		Render();

		frametime=timer.GetTime()-framestart;
	}

	Destruct();

	return 0;
}
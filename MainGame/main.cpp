// program entry point
#include "CMain.h"

CMain main_app;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdline,int nShowCmd)
{
	main_app.Run(lpCmdline);

	return 0;
}
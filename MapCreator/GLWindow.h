#ifndef GLWINDOW
#define GLWINDOW

#include <windows.h>
#include <gl/gl.h>
#pragma comment(lib,"opengl32.lib")

class GLWindow
{
public:
	bool Create(char *,HINSTANCE,int,int,int);
	~GLWindow();
	void DamnedMessages();
	void Message(char *);
	void SetDisplaySettings(int,int,int);

	HWND hwnd;
	bool key[256];
	bool quit;
	HDC hdc;
	HGLRC hrc;
	char *appname;
	int width,height,bpp;

protected:
	static LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);
	MSG msg;
};

#endif
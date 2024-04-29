#ifndef GLWINDOW
#define GLWINDOW

#include <windows.h>
#include <gl/gl.h>
#pragma comment(lib,"opengl32.lib")

class GLWindow
{
public:
	GLWindow();
	~GLWindow();
	bool Create(char *,int,int,int);
	void DamnedMessages();
	void Message(char *);
	void SetDisplaySettings(int,int,int);
	void Close();

	HWND hwnd;
	bool key[256];
	bool run;
	HDC hdc;
	HGLRC hrc;
	char *appname;
	int width,height,bpp;

protected:
	static LRESULT CALLBACK WindowProc(HWND,UINT,WPARAM,LPARAM);
	MSG msg;
	HINSTANCE hinst;
	char *classname;
};

#endif
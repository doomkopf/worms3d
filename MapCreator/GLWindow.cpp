#include "GLWindow.h"

bool GLWindow::Create(char *title,HINSTANCE hInstance,int wi,int h,int b)
{
	WNDCLASSEX w;
	char *classname="clname";
	GLuint PixelFormat;
	appname=title;
	w.cbSize=sizeof(WNDCLASSEX);
	w.style=CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	w.lpfnWndProc=WindowProc;
	w.cbClsExtra=0;
	w.cbWndExtra=0;
	w.hInstance=hInstance;
	w.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	w.hCursor=LoadCursor(NULL,IDC_ARROW);
	w.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	w.lpszMenuName=NULL;
	w.lpszClassName=classname;
	w.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
	if(!RegisterClassEx(&w))
		return false;

	width=wi;
	height=h;
	bpp=b;

	DEVMODE dm;
	ZeroMemory(&dm,sizeof(dm));
	dm.dmSize=sizeof(DEVMODE);
	dm.dmPelsWidth=width;
	dm.dmPelsHeight=height;
	dm.dmBitsPerPel=bpp;
	dm.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
	if(ChangeDisplaySettings(&dm,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		return false;

	hwnd=CreateWindowEx(WS_EX_APPWINDOW,classname,appname,WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,0,0,width,height,NULL,NULL,hInstance,NULL);
	if(!hwnd)
		return false;

	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		bpp,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};
	hdc=GetDC(hwnd);
	if(!hdc)
		return false;
	PixelFormat=ChoosePixelFormat(hdc,&pfd);
	if(!PixelFormat)
		return false;
	if(!SetPixelFormat(hdc,PixelFormat,&pfd))
		return false;
	hrc=wglCreateContext(hdc);
	if(!hrc)
		return false;
	if(!wglMakeCurrent(hdc,hrc))
		return false;

	ShowWindow(hwnd,SW_SHOW);
	SetForegroundWindow(hwnd);
	if(!SetFocus(hwnd))
		return false;

	glViewport(0,0,width,height);
	quit=false;

	return true;
}

void GLWindow::SetDisplaySettings(int w,int h,int b) // does not work
{
	DEVMODE dm;

	ZeroMemory(&dm,sizeof(dm));
	dm.dmSize=sizeof(DEVMODE);
	dm.dmPelsWidth=w;
	dm.dmPelsHeight=h;
	dm.dmBitsPerPel=b;
	dm.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

	if(ChangeDisplaySettings(&dm,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
	{
		ZeroMemory(&dm,sizeof(dm));
		dm.dmSize=sizeof(DEVMODE);
		dm.dmPelsWidth=width;
		dm.dmPelsHeight=height;
		dm.dmBitsPerPel=bpp;
		dm.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		ChangeDisplaySettings(&dm,CDS_FULLSCREEN);
	}
	else
	{
		width=w;
		height=h;
		bpp=b;
		glViewport(0,0,width,height);
	}
}

GLWindow::~GLWindow()
{
	ChangeDisplaySettings(NULL,0);
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(hrc);
	ReleaseDC(hwnd,hdc);
}

void GLWindow::DamnedMessages()
{
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		switch(msg.message)
		{
		case WM_QUIT:
			quit=true;
			break;

		case WM_KEYDOWN:
			key[msg.wParam]=true;
			break;

		case WM_KEYUP:
			key[msg.wParam]=false;
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK GLWindow::WindowProc(HWND hwnd,UINT message,WPARAM wparam,LPARAM lparam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,message,wparam,lparam));
}

void GLWindow::Message(char *text)
{
	MessageBox(hwnd,text,appname,MB_OK);
}
#include "GLWindow.h"

GLWindow::GLWindow()
{
	classname="dirtyclassname";
	run=true;
}

bool GLWindow::Create(char *title,int wi,int h,int b)
{
	WNDCLASS wndclass;
	unsigned int PixelFormat;
	hinst=GetModuleHandle(NULL);

	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hInstance=hinst;
	wndclass.lpfnWndProc=WindowProc;
	wndclass.lpszClassName=classname;
	wndclass.lpszMenuName=NULL;
	wndclass.style=CS_OWNDC;

	if(!RegisterClass(&wndclass))
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

	hwnd=CreateWindow(
		classname,
		"",
		WS_POPUP,
		0,
		0,
		width,
		height,
		NULL,
		NULL,
		hinst,
		NULL);

	if(!hwnd)
		return false;

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	SetFocus(hwnd);

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

	glViewport(0,0,width,height);

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

void GLWindow::DamnedMessages()
{
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		switch(msg.message)
		{
		case WM_QUIT:
			run=false;
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

void GLWindow::Close()
{
	ChangeDisplaySettings(NULL,0);
	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(hrc);
	ReleaseDC(hwnd,hdc);

	if(hwnd)
	{
		DestroyWindow(hwnd);

		while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			DispatchMessage(&msg);
	}

	UnregisterClass(classname,hinst);
}

GLWindow::~GLWindow()
{
	Close();
}
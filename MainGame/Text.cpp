#include "Text.h"
#include "texload.h"
#include "CMain.h"

bool Text::Init(HDC hdc,int x,int y)
{
	screen_x=x;
	screen_y=y;

	base=glGenLists(96);

	font=CreateFont(
		screen_y/25,
		screen_x/100,
		0,
		0,
		FW_BOLD,
		FALSE,
		FALSE,
		FALSE,
		ANSI_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE|DEFAULT_PITCH,
		"Comic Sans Ms");

	SelectObject(hdc,font);
	wglUseFontBitmaps(hdc,32,96,base);

	return true;
}

Text::~Text()
{
	glDeleteLists(base,96);
}

void Text::Print(int x,int y,char *text,...)
{
	char temp[256];
	va_list list;

	if(text==NULL)
		return;

	va_start(list,text);
	vsprintf(temp,text,list);
	va_end(list);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glColor3ub(200,100,0);
	SwitchToOrtho(screen_x,screen_y);

	glListBase(base-32);
	glRasterPos2i(x,y+20);
	glCallLists(strlen(temp),GL_UNSIGNED_BYTE,temp);

	SwitchBack();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glColor3ub(255,255,255);
}

void Text::Print_NO(int x,int y,char *text,...)
{
	char temp[256];
	va_list list;

	if(text==NULL)
		return;

	va_start(list,text);
	vsprintf(temp,text,list);
	va_end(list);

	glDisable(GL_TEXTURE_2D);
	glColor3ub(200,100,0);

	glListBase(base-32);
	glRasterPos2i(x,y+20);
	glCallLists(strlen(temp),GL_UNSIGNED_BYTE,temp);

	glEnable(GL_TEXTURE_2D);
	glColor3ub(255,255,255);
}
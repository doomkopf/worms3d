#ifndef CTEXT
#define CTEXT

#include <windows.h>
#include <gl/gl.h>
#include <stdio.h>

class Text
{
public:
	bool Init(HDC,int,int);
	~Text();
	void Print(int,int,char *,...);
	void Print_NO(int,int,char *,...);

protected:
	int base;
	//GLuint font_tex;
	HFONT font;
	int screen_x,screen_y;
};

#endif
#include "proc.h"
#include <windows.h>
#include <gl/gl.h>
#include <stdio.h>
#include "texload.h"

void ScreenShot(char *fname,int x,int y)
{
	t_rgb *data_rgb;
	FILE *file1;
	TGAHeader header;
	unsigned char swap;

	file1=fopen(fname,"w+b");
	if(!file1)
		return;

	data_rgb = new t_rgb[x*y];
	ZeroMemory(&header,sizeof(header));

	header.image_type=2;
	header.width=x;
	header.height=y;
	header.pixel_size=24;

	glReadPixels(0,0,x,y,GL_RGB,GL_UNSIGNED_BYTE,data_rgb);

	for(int i=0;i<x*y;i++)
	{
		swap=data_rgb[i].r;
		data_rgb[i].r=data_rgb[i].b;
		data_rgb[i].b=swap;
	}

	//fwrite(&header,sizeof(header),1,file1);
	fwrite(&header.id_length,sizeof(unsigned char),1,file1);
	fwrite(&header.colormap_type,sizeof(unsigned char),1,file1);
	fwrite(&header.image_type,sizeof(unsigned char),1,file1);
	fwrite(&header.colormap_index,sizeof(unsigned short),1,file1);
	fwrite(&header.colormap_length,sizeof(unsigned short),1,file1);
	fwrite(&header.colormap_size,sizeof(unsigned char),1,file1);
	fwrite(&header.x_origin,sizeof(unsigned short),1,file1);
	fwrite(&header.y_origin,sizeof(unsigned short),1,file1);
	fwrite(&header.width,sizeof(unsigned short),1,file1);
	fwrite(&header.height,sizeof(unsigned short),1,file1);
	fwrite(&header.pixel_size,sizeof(unsigned char),1,file1);
	fwrite(&header.attributes,sizeof(unsigned char),1,file1);

	fwrite(data_rgb,sizeof(t_rgb),x*y,file1);

	fclose(file1);
	delete [] data_rgb;
}

void SwitchToOrtho(int width,int height)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,width,height,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void SwitchBack()
{
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
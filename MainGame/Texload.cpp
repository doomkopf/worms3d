#include "texload.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>

bool LoadTextureTGA(char *file,unsigned int *tex)
{
	unsigned char *tga_data;
	int image_size;
	int bppixel;
	unsigned char swap;
	int type;

	TGAHeader tga;

	FILE *file1=fopen(file,"rb");
	if(!file1)
		return false;

	fread( &tga.id_length, sizeof(unsigned char), 1, file1 );
	fread( &tga.colormap_type, sizeof(unsigned char), 1, file1 );
	fread( &tga.image_type, sizeof(unsigned char), 1, file1 );

	fread( &tga.colormap_index, sizeof(unsigned short), 1, file1 );
	fread( &tga.colormap_length, sizeof(unsigned short), 1, file1 );

	fread( &tga.colormap_size, sizeof(unsigned char), 1, file1 );

	fread( &tga.x_origin, sizeof(unsigned short), 1, file1 );
	fread( &tga.y_origin, sizeof(unsigned short), 1, file1 );
	fread( &tga.width, sizeof(unsigned short), 1, file1 );
	fread( &tga.height, sizeof(unsigned short), 1, file1 );

	fread( &tga.pixel_size, sizeof(unsigned char), 1, file1 );
	fread( &tga.attributes, sizeof(unsigned char), 1, file1 );

	if(tga.image_type!=2)
		return false;

	switch(tga.pixel_size)
	{
	case 24:
		type=GL_RGB;
		break;

	case 32:
		type=GL_RGBA;
		break;

	default:
		return false;
	}

	bppixel=tga.pixel_size/8;
	image_size=tga.width*tga.height*bppixel;

	tga_data = new unsigned char[image_size];
	if((signed)fread(tga_data,1,image_size,file1)!=image_size)
	{
		fclose(file1);
		return false;
	}

	for(int i=0;i<image_size;i+=bppixel)
	{
		swap=tga_data[i];
		tga_data[i]=tga_data[i+2];
		tga_data[i+2]=swap;
	}
	fclose(file1);

	glGenTextures(1,tex);
	glBindTexture(GL_TEXTURE_2D,*tex);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D,bppixel,tga.width,tga.height,type,GL_UNSIGNED_BYTE,tga_data);

	delete [] tga_data;

	return true;
}
#ifndef CTEXTURELOADER
#define CTEXTURELOADER

#include "textures.h"

class CTextureLoader
{
public:
	bool LoadTextures();
	unsigned int GetTexture(int);

protected:
	unsigned int texture[NUM_TEXTURES];
};

#endif
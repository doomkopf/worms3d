#include "CTextureLoader.h"
#include "texload.h"

bool CTextureLoader::LoadTextures()
{
	if(!LoadTextureTGA("textures/ice1.tga",&texture[TEX_ICE1]))
		return false;
	if(!LoadTextureTGA("textures/ice2.tga",&texture[TEX_ICE2]))
		return false;
	if(!LoadTextureTGA("textures/grass1.tga",&texture[TEX_GRASS1]))
		return false;
	if(!LoadTextureTGA("textures/grass2.tga",&texture[TEX_GRASS2]))
		return false;

	if(!LoadTextureTGA("textures/water1.tga",&texture[TEX_WATER1]))
		return false;
	if(!LoadTextureTGA("textures/sky1.tga",&texture[TEX_SKY1]))
		return false;

	if(!LoadTextureTGA("textures/newgame.tga",&texture[TEX_NEWGAME]))
		return false;
	if(!LoadTextureTGA("textures/options.tga",&texture[TEX_OPTIONS]))
		return false;
	if(!LoadTextureTGA("textures/quit.tga",&texture[TEX_QUIT]))
		return false;
	if(!LoadTextureTGA("textures/back.tga",&texture[TEX_BACK]))
		return false;
	if(!LoadTextureTGA("textures/start.tga",&texture[TEX_START]))
		return false;
	if(!LoadTextureTGA("textures/arrow.tga",&texture[TEX_ARROW]))
		return false;
	if(!LoadTextureTGA("textures/shademode.tga",&texture[TEX_SHADEMODE]))
		return false;

	if(!LoadTextureTGA("textures/particle_rock1.tga",&texture[TEX_PARTICLE_ROCK1]))
		return false;

	if(!LoadTextureTGA("meshes/potator.tga",&texture[TEX_TEAM1]))
		return false;
	if(!LoadTextureTGA("meshes/madpear.tga",&texture[TEX_TEAM2]))
		return false;

	if(!LoadTextureTGA("meshes/grenade.tga",&texture[TEX_GRENADE]))
		return false;

	if(!LoadTextureTGA("textures/logo.tga",&texture[TEX_LOGO]))
		return false;

	return true;
}

unsigned int CTextureLoader::GetTexture(int tex)
{
	if(tex>=NUM_TEXTURES)
		return -1;

	return texture[tex];
}
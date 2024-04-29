#ifndef CMAIN
#define CMAIN

#include "GLWindow.h"
#include "CControl.h"
#include "CMap.h"
#include "Camera.h"
#include "Timer.h"
#include "CPlayer.h"
#include "CMenu.h"
#include "CTextureLoader.h"
#include "CMeshLoader.h"
#include "CSound.h"
#include "CGame.h"
#include "proc.h"

class CMain
{
public:
	CMain();
	void Run(LPSTR);
	GLWindow *GetMainWindow();
	Camera *GetCamera();
	CControl *GetControl();
	CMap *GetMap();
	CMenu *GetMenu();
	CTextureLoader *GetTextureLoader();
	CMeshLoader *GetMeshLoader();
	CSound *GetSound();
	CGame *GetGame();
	Timer *GetTimer();

	bool run;
	float frametime;

protected:
	bool Init(LPSTR);
	void InitGL();
	void GetInput();
	void Render();
	void DrawLogo();

	GLWindow win;
	CControl control;
	CMap map;
	Camera cam;
	Timer timer;
	CMenu menu;
	CTextureLoader textureloader;
	CMeshLoader meshloader;
	CSound sound;
	CGame game;
	unsigned int logo_tex;
};

#endif
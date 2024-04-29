#include "CMain.h"
#include <gl/glu.h>
#include "texload.h"
#include <time.h>
#pragma comment (lib,"glu32.lib")

CMain::CMain()
{
}

bool CMain::Init(LPSTR cmdline)
{
	run=false;
	int w,h,bits;

	if(strcmp(cmdline,"")!=0)
		sscanf(cmdline,"%dx%dx%d",&w,&h,&bits);
	else
	{
		w=1024;
		h=768;
		bits=16;
	}

	if(!win.Create(VERSION,w,h,bits))
	{
		win.Message("Error creating window");
		return false;
	}

	srand((unsigned)time(NULL));

	InitGL();

	if(!control.Init())
	{
		win.Message("Error initializing controls");
		return false;
	}

	timer.Init();

	if(!sound.Init())
		return false;

	if(!textureloader.LoadTextures())
		return false;
	if(!meshloader.LoadMeshes())
		return false;

	if(!menu.Init())
		return false;

	frametime=0;
	logo_tex=textureloader.GetTexture(TEX_LOGO);

	return true;
}

void CMain::InitGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(float)win.width/(float)win.height,8.0f,16384.0f);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.5,0.5f,1.0f,0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/*glFogi(GL_FOG_MODE,GL_LINEAR);
	float f_color[]={0.4f,0.4f,0.6f,1.0f};
	glFogfv(GL_FOG_COLOR,f_color);
	glHint(GL_FOG_HINT,GL_DONT_CARE);
	glFogf(GL_FOG_START,500.0f);
	glFogf(GL_FOG_END,2000.0f);*/

	//glPointSize(10.0f);
}

void CMain::Run(LPSTR cmdline)
{
	float t=timer.GetTime(),framestart;
	int sc=0;
	char str[16];

	if(Init(cmdline))
		run=true;

	while(run)
	{
		framestart=t;
		// -------- frame start --------

		win.DamnedMessages();

		if(win.key[VK_ESCAPE])
			run=false;

		GetInput();

		game.Update();

		Render();

		if(control.hit_d[KEY_F12])
		{
			sprintf(str,"shot%d.tga",sc++);
			ScreenShot(str,win.width,win.height);
		}

		if(control.key_d[KEY_A])
			Sleep(100);

		// -------- frame end --------
		t=timer.GetTime();
		frametime=t-framestart;
	}
}

void CMain::GetInput()
{
	control.Update();

	if(control.hit_d[KEY_TAB])
		menu.active=!menu.active;

	if(menu.active)
		menu.GetInput();
	else if(map.loaded)
	{
		game.GetCurrentPlayer()->GetInput();
	}
}

void CMain::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	map.DrawSky();
	map.DrawLand();
	map.DrawStuff();

	game.DrawStuff();

	if(map.loaded)
		game.GetCurrentPlayer()->DrawCrosshair();
	else
		DrawLogo();

	menu.Draw();

	CPlayer *temp_player=game.GetCurrentPlayer();
	menu.text.Print(0,0,"FPS: %4.1f",1000/frametime);
	menu.text.Print(0,20,"Pos - X: %4.1f  Y: %4.1f  Z: %4.1f",
		temp_player->position.xyz[0],
		temp_player->position.xyz[1],
		temp_player->position.xyz[2]);
	menu.text.Print(0,40,"DirVector - X: %4.1f  Y: %4.1f  Z: %4.1f",
		temp_player->direction.xyz[0],
		temp_player->direction.xyz[1],
		temp_player->direction.xyz[2]);
	menu.text.Print(0,60,"Force: %4.1f",temp_player->force);
	menu.text.Print(0,80,"Weapon: %d",temp_player->cur_weapon);
	menu.text.Print(0,100,"Health: %d",temp_player->health);
	if(temp_player->onground)
		menu.text.Print(0,120,"OnGround");

	SwapBuffers(win.hdc);
}

void CMain::DrawLogo()
{
	glDisable(GL_DEPTH_TEST);
	SwitchToOrtho(win.width,win.height);

	glBindTexture(GL_TEXTURE_2D,logo_tex);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(0,(float)win.height);
	glTexCoord2f(1,0);
	glVertex2f((float)win.width,(float)win.height);
	glTexCoord2f(1,1);
	glVertex2f((float)win.width,0);
	glTexCoord2f(0,1);
	glVertex2f(0,0);
	glEnd();

	SwitchBack();
	glEnable(GL_DEPTH_TEST);
	glColor3ub(255,255,255);
}

GLWindow *CMain::GetMainWindow()
{
	return &win;
}

Camera *CMain::GetCamera()
{
	return &cam;
}

CControl *CMain::GetControl()
{
	return &control;
}

CMap *CMain::GetMap()
{
	return &map;
}

CMenu *CMain::GetMenu()
{
	return &menu;
}

CTextureLoader *CMain::GetTextureLoader()
{
	return &textureloader;
}

CMeshLoader *CMain::GetMeshLoader()
{
	return &meshloader;
}

CSound *CMain::GetSound()
{
	return &sound;
}

CGame *CMain::GetGame()
{
	return &game;
}

Timer *CMain::GetTimer()
{
	return &timer;
}
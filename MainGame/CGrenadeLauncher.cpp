#include "CGrenadeLauncher.h"
#include "CMain.h"

extern CMain main_app;

CGrenadeLauncher::CGrenadeLauncher()
{
	force=0;
	loading=false;
	l_inc=true;
}

void CGrenadeLauncher::Shoot(CVector3f &pos,CVector3f &vec,bool key_down)
{
	if(main_app.GetControl()->hit[SHOOT])
		loading=true;

	if(loading)
	{
		if(l_inc)
			force+=main_app.frametime*0.01f;
		else
			force-=main_app.frametime*0.01f;

		if(force>=20)
		{
			l_inc=false;
			force=20;
		}
		else if(force<=0)
		{
			l_inc=true;
			force=0;
		}

		if(!key_down)
		{
			main_app.GetGame()->StartNewGrenade(pos,vec,force);
			force=0;
			loading=false;
		}
	}
}

void CGrenadeLauncher::Update()
{
}

void CGrenadeLauncher::Draw()
{
}

void CGrenadeLauncher::DrawInterface()
{
	main_app.GetMenu()->text.Print(0,140,"G_Launcher: %4.1f",force);
}
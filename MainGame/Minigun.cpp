#include "Minigun.h"
#include "CMain.h"

extern CMain main_app;

#define MINIGUN_SPREAD_FACTOR 0.0125f

CMinigun::CMinigun()
{
	last_time=main_app.GetTimer()->GetTime();
}

void CMinigun::Shoot(CVector3f &pos,CVector3f &vec,bool key_down)
{
	if(!key_down)
		return;

	float time=main_app.GetTimer()->GetTime();
	if((time-last_time)>100)
	{
		last_time=time;
		main_app.GetSound()->Play(SND_MINIGUN);

		start=pos;
		dir=vec;
		dir.xyz[0]+=float((rand()%20)-10)*MINIGUN_SPREAD_FACTOR;
		dir.xyz[1]+=float((rand()%20)-10)*MINIGUN_SPREAD_FACTOR;
		dir.xyz[2]+=float((rand()%20)-10)*MINIGUN_SPREAD_FACTOR;
		dir.Normalize();

		CGame *game=main_app.GetGame();
		CPlayer *player=game->GetPlayers();
		for(int i=0;i<game->GetPlayerCount();i++)
		{
			if(i==game->GetCurrentPlayerIndex())
				continue;

			if(GetDistance_ray_point(pos,dir,player[i].position)<OBJECT_RADIUS)
			{
				player[i].force_dir=dir;
				player[i].extra_force=2;
			}
		}

		CVector3f p;
		if(main_app.GetMap()->GetCollisionPoint(pos+(dir*400),dir,&p))
		{
			main_app.GetMap()->DeformGeometry(p,50);
			//main_app.GetMap()->StartNewParticleSource(p.xyz[0],p.xyz[1],p.xyz[2],1,false);
		}
	}
}

void CMinigun::Draw()
{
	/*glDisable(GL_TEXTURE_2D);
	glLineWidth(5);

	glBegin(GL_LINES);
	glVertex3fv(start.xyz);
	glVertex3fv((start+(dir*100)).xyz);
	glEnd();

	glEnable(GL_TEXTURE_2D);*/
}
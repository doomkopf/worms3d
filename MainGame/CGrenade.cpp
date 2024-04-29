#include "CGrenade.h"
#include "math.h"
#include "CMain.h"

extern CMain main_app;

CGrenade::CGrenade()
{
	active=false;
}

void CGrenade::Start(CVector3f &pos,CVector3f &vec,float f)
{
	if(active)
		return;

	extra_force=f;
	position=pos;
	destination=position;
	xrot=yrot=0;
	force_dir=vec;
	onground=false;
	active=true;
	force=90-GetAngle_vv(CVector3f(0,1,0),vec);

	main_app.GetSound()->Play(SND_GRENADE_SHOT);
}

void CGrenade::Update()
{
	CVector3f p;
	CMap *map;
	CGame *game;

	if(!active)
		return;

	map=main_app.GetMap();
	game=main_app.GetGame();
	speed=main_app.frametime*0.1f;
	UpdatePhysics();

	if(map->GetCollisionPoint(this,&p))
	{
		main_app.GetSound()->Play(SND_GRENADE_EXPLOSION);
		map->DeformGeometry(p,200);
		CPlayer *player=game->GetPlayers();
		for(int i=0;i<game->GetPlayerCount();i++)
		{
			CVector3f v=player[i].position-p;
			if(v.Length()<200)
			{
				player[i].force_dir=VectorNormalize(v);
				player[i].extra_force=10;
				//player[i].health-=20;
			}
		}
		active=false;
		map->StartNewParticleSource(p.xyz[0],p.xyz[1],p.xyz[2],1,false);
	}

	if(position.xyz[1]<0)
		active=false;

	direction=VectorNormalize(destination-position);

	position=destination;
}

void CGrenade::DrawExtra()
{
}
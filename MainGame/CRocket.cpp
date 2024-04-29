#include "CRocket.h"
#include "CMain.h"

extern CMain main_app;

CRocket::CRocket()
{
	active=false;
}

void CRocket::Start(CVector3f &pos,CVector3f &vec)
{
	if(active)
		return;

	position=destination=pos;
	xrot=yrot=0;
	direction=vec;
	onground=false;
	active=true;

	main_app.GetSound()->Play(SND_ROCKET_SHOT);
	main_app.GetGame()->ActionStart();
}

void CRocket::Update()
{
	CVector3f p;
	CMap *map;
	CGame *game;

	if(!active)
		return;

	map=main_app.GetMap();
	game=main_app.GetGame();

	destination+=direction*main_app.frametime;

	if(destination.xyz[0]<(map->box_min.xyz[0]-1000) ||
		destination.xyz[1]<map->box_min.xyz[1] ||
		destination.xyz[2]<(map->box_min.xyz[2]-1000) ||
		destination.xyz[0]>(map->box_max.xyz[0]+1000) ||
		destination.xyz[1]>(map->box_max.xyz[1]+1000) ||
		destination.xyz[2]>(map->box_max.xyz[2]+1000))
	{
		active=false;
	}
	else if(map->GetCollisionPoint(this,&p))
	{
		main_app.GetSound()->Play(SND_GRENADE_EXPLOSION);
		main_app.GetGame()->ActionEnd();
		map->DeformGeometry(p,200);
		CPlayer *player=game->GetPlayers();
		for(int i=0;i<game->GetPlayerCount();i++)
		{
			CVector3f v=player[i].position-p;
			if(v.Length()<200)
			{
				player[i].force_dir=VectorNormalize(v);
				player[i].extra_force=10;
				player[i].health-=20;
			}
		}
		if(!main_app.GetControl()->key[SHOOT]) // just for fun
			active=false;
		map->StartNewParticleSource(p.xyz[0],p.xyz[1],p.xyz[2],1,false);
	}

	position=destination;
}
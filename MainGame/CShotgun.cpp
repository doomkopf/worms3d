#include "CShotgun.h"
#include "CMain.h"

extern CMain main_app;

void CShotgun::Shoot(CVector3f &pos,CVector3f &vec,bool key_down)
{
	if(main_app.GetControl()->hit[SHOOT])
	{
		CGame *game=main_app.GetGame();
		CPlayer *player=game->GetPlayers();

		main_app.GetSound()->Play(SND_SHOTGUN);

		for(int i=0;i<game->GetPlayerCount();i++)
		{
			if(i==game->GetCurrentPlayerIndex())
				continue;

			if(GetDistance_ray_point(pos,vec,player[i].position)<OBJECT_RADIUS)
			{
				player[i].force_dir=vec;
				player[i].extra_force=5;
			}
		}

		CVector3f p;
		if(main_app.GetMap()->GetCollisionPoint(pos,vec,&p))
			main_app.GetMap()->DeformGeometry(p,50);
	}
}
#include "CJetpack.h"
#include "CMain.h"

extern CMain main_app;

void CJetpack::Shoot(CVector3f &pos,CVector3f &vec,bool key_down)
{
	CPlayer *player;

	if(main_app.GetControl()->hit[SHOOT])
		main_app.GetSound()->Play(SND_JETPACK,SND_INFINITE);

	if(key_down)
	{
		player=main_app.GetGame()->GetCurrentPlayer();

		if(player->force>=-90)
			player->onground=false;

		player->force+=0.3f*main_app.frametime;
		if(player->force>90)
			player->force=90;

		if(player->extra_force<=1)
		{
			player->force_dir.Set(0,0,0);
		}
	}
	else
		main_app.GetSound()->Stop(SND_JETPACK);
}
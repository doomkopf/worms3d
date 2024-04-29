#include "CGame.h"
#include "CMain.h"

extern CMain main_app;

CGame::CGame()
{
	int i;

	for(i=0;i<8;i++)
	{
		grenade[i].SetModel(main_app.GetMeshLoader()->GetStaticModel(S_MODEL_GRENADE));
		rocket[i].SetModel(main_app.GetMeshLoader()->GetStaticModel(S_MODEL_GRENADE));
	}

	cur_team=1;
}

bool CGame::Start(char *map,int n)
{
	char temp[64];

	num_per_team=n;

	strcpy(temp,"maps/");
	strcat(temp,map);

	if(!main_app.GetMap()->Load(temp))
		return false;

	main_app.GetMap()->SetValidPlayerPositions();

	cur_player=0;
	player[0].active=true;
	action=NONE;

	for(int i=0;i<num_per_team;i++)
	{
		player[i].SetModel(main_app.GetMeshLoader()->GetAnimModel(A_MODEL_TEAM1));
		player[i].team=1;
	}
	for(;i<num_per_team*2;i++)
	{
		player[i].SetModel(main_app.GetMeshLoader()->GetAnimModel(A_MODEL_TEAM2));
		player[i].team=2;
	}

	return true;
}

void CGame::Update()
{
	CMap *map=main_app.GetMap();

	if(map->loaded)
	{
		map->Update();

		// update players
		for(int i=0;i<GetPlayerCount();i++)
		{
			player[i].Update();
			//if(player[i].position.y<32 || player[i].health<=0)
				//player[i].dead=true;
			if(player[i].position.xyz[1]<0)
				player[i].position.xyz[1]=0;
		}

		player[cur_player].SetView();

		if(main_app.GetControl()->hit_d[KEY_RCONTROL])
			ChangePlayer();
		if(main_app.GetControl()->hit_d[KEY_T])
			ChangeTeam();
		if(action==ENDED)
		{
			//ChangeTeam();
			action=NONE;
		}

		// update other stuff
		for(i=0;i<8;i++)
		{
			grenade[i].Update();
			rocket[i].Update();
		}
	}
}

void CGame::StartNewGrenade(CVector3f &pos,CVector3f &vec,float force)
{
	for(int i=0;i<8;i++)
	{
		if(!grenade[i].active)
		{
			grenade[i].Start(pos,vec,force);
			break;
		}
	}
}

void CGame::StartNewRocket(CVector3f &pos,CVector3f &vec)
{
	for(int i=0;i<8;i++)
	{
		if(!rocket[i].active)
		{
			rocket[i].Start(pos,vec);
			break;
		}
	}
}

void CGame::DrawStuff()
{
	for(int i=0;i<GetPlayerCount();i++)
	{
		if(!player[i].dead)
			player[i].DrawModel();
		player[i].DrawStuff();
	}

	for(i=0;i<8;i++)
	{
		grenade[i].Draw();
		rocket[i].Draw();
	}
}

void CGame::ActionStart()
{
	action=STARTED;
}

void CGame::ActionEnd()
{
	action=ENDED;
}

void CGame::ChangePlayer()
{
	player[cur_player++].active=false;

	switch(cur_team)
	{
	case 1:
		if(cur_player>=num_per_team)
			cur_player=0;
		break;

	case 2:
		if(cur_player>=num_per_team*2)
			cur_player=num_per_team;
		break;
	}

	if(player[cur_player].dead)
		ChangePlayer();

	player[cur_player].active=true;
}

void CGame::ChangeTeam()
{
	if(cur_team==1)
	{
		cur_team=2;
		player[cur_player].active=false;
		cur_player=num_per_team;
		player[cur_player].active=true;
	}
	else
	{
		cur_team=1;
		player[cur_player].active=false;
		cur_player=0;
		player[cur_player].active=true;
	}
}

CPlayer *CGame::GetPlayers()
{
	return player;
}

CPlayer *CGame::GetCurrentPlayer()
{
	return &player[cur_player];
}

int CGame::GetCurrentPlayerIndex()
{
	return cur_player;
}

int CGame::GetPlayerCount()
{
	return num_per_team*2;
}
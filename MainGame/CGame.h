#ifndef CGAME
#define CGAME

#include "CPlayer.h"
#include "CGrenade.h"
#include "CRocket.h"

typedef enum
{
	STARTED,ENDED,NONE
} t_action;

class CGame
{
public:
	CGame();
	bool Start(char *,int);
	void Update();
	void StartNewGrenade(CVector3f &,CVector3f &,float);
	void StartNewRocket(CVector3f &,CVector3f &);
	void DrawStuff();
	CPlayer *GetPlayers();
	CPlayer *GetCurrentPlayer();
	int GetCurrentPlayerIndex();
	int GetPlayerCount();
	void ActionStart();
	void ActionEnd();
	void ChangePlayer();
	void ChangeTeam();

protected:
	CPlayer player[8];
	CGrenade grenade[8];
	CRocket rocket[8];
	int cur_player;
	int num_per_team;
	int cur_team;
	t_action action;
};

#endif
#ifndef CMENU
#define CMENU

#include "Text.h"
#include "CControl.h"
#include "defs.h"

typedef enum
{
	MAIN,NEW_GAME,OPTIONS
} t_menu;

class CMenu
{
public:
	bool Init();
	void Draw();
	void GetInput();

	bool active;
	Text text;

protected:
	void DrawDarkShade();
	void DrawCursor();
	void DrawMain();
	void DrawNewGame();
	void DrawOptions();
	void DrawButton(point2f &,point2f &,bool,bool);
	bool FindMaps();
	void StartNewGame();

	t_menu location;
	int screen_x,screen_y;
	CControl *control;
	point2f mouse;
	char maps[128][64];
	int num_maps,cur_map,num_per_team;
	unsigned int d_shade,newgame_tex,options_tex,quit_tex,back_tex,start_tex,arrow_tex,
		shademode_tex;

	point2f newgame_pos,newgame_max;
	point2f options_pos,options_max;
	point2f quit_pos,quit_max;

	point2f back_pos,back_max;

	point2f start_pos,start_max;
	point2f num_players_pos;
	point2f inc_players_pos,inc_players_max;
	point2f dec_players_pos,dec_players_max;
	point2f nextmap_pos,nextmap_max;
	point2f prevmap_pos,prevmap_max;
	point2f maps_pos;

	point2f switch_shademode_pos,switch_shademode_max;
	point2f shademode_text;
	char *shademodes[3];
	int cur_shade;
};

#endif
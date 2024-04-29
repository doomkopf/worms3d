#include "CMenu.h"
#include "CMain.h"
#include "texload.h"
#include "CPlayer.h"

extern CMain main_app;

bool CMenu::Init()
{
	unsigned char d_shade_data[]={
		0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255,
		255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0,
		0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255,
		255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0,
		0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255,
		255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0,
		0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255,
		255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0, 255,255,255, 0,0,0
	};

	screen_x=main_app.GetMainWindow()->width;
	screen_y=main_app.GetMainWindow()->height;
	mouse.x=float(screen_x/2);
	mouse.y=float(screen_y/2);
	control=main_app.GetControl();
	text.Init(main_app.GetMainWindow()->hdc,screen_x,screen_y);

	glBindTexture(GL_TEXTURE_2D,d_shade);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,3,8,8,0,GL_RGB,GL_UNSIGNED_BYTE,d_shade_data);

	newgame_tex=main_app.GetTextureLoader()->GetTexture(TEX_NEWGAME);
	options_tex=main_app.GetTextureLoader()->GetTexture(TEX_OPTIONS);
	quit_tex=main_app.GetTextureLoader()->GetTexture(TEX_QUIT);
	back_tex=main_app.GetTextureLoader()->GetTexture(TEX_BACK);
	start_tex=main_app.GetTextureLoader()->GetTexture(TEX_START);
	arrow_tex=main_app.GetTextureLoader()->GetTexture(TEX_ARROW);
	shademode_tex=main_app.GetTextureLoader()->GetTexture(TEX_SHADEMODE);

	if(!FindMaps())
		return false;

	newgame_pos.x=(float)screen_x/2;
	newgame_pos.y=(float)screen_y*0.125f;
	newgame_max.x=(float)screen_x*0.125f;
	newgame_max.y=(float)screen_y*0.03125f;

	options_pos.x=(float)screen_x/2;
	options_pos.y=(float)screen_y*0.25f;
	options_max.x=(float)screen_x*0.125f;
	options_max.y=(float)screen_y*0.03125f;

	quit_pos.x=(float)screen_x/2;
	quit_pos.y=(float)screen_y*0.875f;
	quit_max.x=(float)screen_x*0.125f;
	quit_max.y=(float)screen_y*0.03125f;

	start_pos.x=(float)screen_x/2;
	start_pos.y=(float)screen_y*0.75f;
	start_max.x=(float)screen_x*0.125f;
	start_max.y=(float)screen_y*0.03125f;

	back_pos.x=(float)screen_x/2;
	back_pos.y=(float)screen_y*0.875f;
	back_max.x=(float)screen_x*0.125f;
	back_max.y=(float)screen_y*0.03125f;

	num_players_pos.x=(float)screen_x/2;
	num_players_pos.y=(float)screen_y*0.25f;

	inc_players_pos.x=(float)screen_x*0.875f;
	inc_players_pos.y=(float)screen_y*0.25f;
	inc_players_max.x=(float)screen_x*0.03125f;
	inc_players_max.y=(float)screen_y*0.03125f;
	dec_players_pos.x=(float)screen_x*0.75f;
	dec_players_pos.y=(float)screen_y*0.25f;
	dec_players_max.x=(float)screen_x*0.03125f;
	dec_players_max.y=(float)screen_y*0.03125f;

	maps_pos.x=(float)screen_x/2;
	maps_pos.y=(float)screen_y*0.625f;

	nextmap_pos.x=(float)screen_x*0.75f;
	nextmap_pos.y=(float)screen_y*0.625f;
	nextmap_max.x=(float)screen_x*0.03125f;
	nextmap_max.y=(float)screen_y*0.03125f;
	prevmap_pos.x=(float)screen_x*0.25f;
	prevmap_pos.y=(float)screen_y*0.625f;
	prevmap_max.x=(float)screen_x*0.03125f;
	prevmap_max.y=(float)screen_y*0.03125f;

	switch_shademode_pos.x=(float)screen_x*0.25f;
	switch_shademode_pos.y=(float)screen_y*0.25f;
	switch_shademode_max.x=(float)screen_x*0.125f;
	switch_shademode_max.y=(float)screen_y*0.03125f;
	shademode_text.x=(float)screen_x/2;
	shademode_text.y=(float)screen_y*0.25f;

	shademodes[0]="No shade";
	shademodes[1]="Flat";
	shademodes[2]="Gouraud";

	cur_shade=2;
	num_per_team=1;
	location=MAIN;
	active=true;

	return true;
}

void CMenu::GetInput()
{
	if(!control->hit_d[KEY_MLEFT])
		return;

	switch(location)
	{
	case MAIN:
		if(mouse.x>-newgame_max.x+newgame_pos.x && // click on new game button
			mouse.y>-newgame_max.y+newgame_pos.y &&
			mouse.x<newgame_max.x+newgame_pos.x &&
			mouse.y<newgame_max.y+newgame_pos.y)
		{
			location=NEW_GAME;
			main_app.GetMap()->Destruct();
		}
		else if(mouse.x>-options_max.x+options_pos.x && // click on options button
			mouse.y>-options_max.y+options_pos.y &&
			mouse.x<options_max.x+options_pos.x &&
			mouse.y<options_max.y+options_pos.y)
		{
			location=OPTIONS;
		}
		else if(mouse.x>-quit_max.x+quit_pos.x && // click on quit button
			mouse.y>-quit_max.y+quit_pos.y &&
			mouse.x<quit_max.x+quit_pos.x &&
			mouse.y<quit_max.y+quit_pos.y)
			main_app.run=false;
		break;

	case NEW_GAME:
		if(mouse.x>-dec_players_max.x+dec_players_pos.x && // click on dec_players button
			mouse.y>-dec_players_max.y+dec_players_pos.y &&
			mouse.x<dec_players_max.x+dec_players_pos.x &&
			mouse.y<dec_players_max.y+dec_players_pos.y)
		{
			num_per_team--;
			if(num_per_team<1)
				num_per_team=1;
		}
		else if(mouse.x>-inc_players_max.x+inc_players_pos.x && // click on inc_players button
			mouse.y>-inc_players_max.y+inc_players_pos.y &&
			mouse.x<inc_players_max.x+inc_players_pos.x &&
			mouse.y<inc_players_max.y+inc_players_pos.y)
		{
			num_per_team++;
			if(num_per_team>4)
				num_per_team=4;
		}
		else if(mouse.x>-prevmap_max.x+prevmap_pos.x && // click on prevmap button
			mouse.y>-prevmap_max.y+prevmap_pos.y &&
			mouse.x<prevmap_max.x+prevmap_pos.x &&
			mouse.y<prevmap_max.y+prevmap_pos.y)
		{
			cur_map--;
			if(cur_map<0)
				cur_map=0;
		}
		else if(mouse.x>-nextmap_max.x+nextmap_pos.x && // click on nextmap button
			mouse.y>-nextmap_max.y+nextmap_pos.y &&
			mouse.x<nextmap_max.x+nextmap_pos.x &&
			mouse.y<nextmap_max.y+nextmap_pos.y)
		{
			cur_map++;
			if(cur_map>num_maps-1)
				cur_map=num_maps-1;
		}
		else if(mouse.x>-start_max.x+start_pos.x && // click on start button
			mouse.y>-start_max.y+start_pos.y &&
			mouse.x<start_max.x+start_pos.x &&
			mouse.y<start_max.y+start_pos.y)
		{
			StartNewGame();
		}
		else if(mouse.x>-back_max.x+back_pos.x && // click on back button
			mouse.y>-back_max.y+back_pos.y &&
			mouse.x<back_max.x+back_pos.x &&
			mouse.y<back_max.y+back_pos.y)
		{
			location=MAIN;
		}
		break;

	case OPTIONS:
		if(mouse.x>-switch_shademode_max.x+switch_shademode_pos.x && // click on back button
			mouse.y>-switch_shademode_max.y+switch_shademode_pos.y &&
			mouse.x<switch_shademode_max.x+switch_shademode_pos.x &&
			mouse.y<switch_shademode_max.y+switch_shademode_pos.y)
		{
			cur_shade++;
			if(cur_shade>2)
				cur_shade=0;
			CMap *map=main_app.GetMap();
			switch(cur_shade)
			{
			case 0:
				map->shademode=NO_SHADE;
				break;

			case 1:
				map->shademode=FLAT;
				break;

			case 2:
				map->shademode=GOURAUD;
				break;
			}
		}
		else if(mouse.x>-back_max.x+back_pos.x && // click on back button
			mouse.y>-back_max.y+back_pos.y &&
			mouse.x<back_max.x+back_pos.x &&
			mouse.y<back_max.y+back_pos.y)
		{
			location=MAIN;
		}
		break;
	}
}

void CMenu::DrawDarkShade()
{
	glLoadIdentity();
	//glColor4ub(255,255,255,0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR,GL_ZERO);

	glBindTexture(GL_TEXTURE_2D,d_shade);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(0,(float)screen_y);
	glTexCoord2f(1000,0);
	glVertex2f((float)screen_x,(float)screen_y);
	glTexCoord2f(1000,750);
	glVertex2f((float)screen_x,0);
	glTexCoord2f(0,750);
	glVertex2f(0,0);
	glEnd();

	glDisable(GL_BLEND);
}

void CMenu::DrawCursor()
{
	glLoadIdentity();

	mouse.x+=control->mouse_x*4;
	mouse.y+=control->mouse_y*4;
	if(mouse.x>screen_x)
		mouse.x=(float)screen_x;
	if(mouse.x<0)
		mouse.x=0;
	if(mouse.y>screen_y)
		mouse.y=(float)screen_y;
	if(mouse.y<0)
		mouse.y=0;

	glDisable(GL_TEXTURE_2D);
	glColor3ub(0,0,255);
	glLoadIdentity();
	glTranslatef(mouse.x,mouse.y,0);

	glBegin(GL_TRIANGLES);
	glVertex2f(0,0);
	glVertex2f(0,10);
	glVertex2f(10,10);
	glEnd();

	glEnable(GL_TEXTURE_2D);
}

void CMenu::DrawMain()
{
	// draw new game button
	glBindTexture(GL_TEXTURE_2D,newgame_tex);
	DrawButton(newgame_pos,newgame_max,false,false);

	// draw options button
	glBindTexture(GL_TEXTURE_2D,options_tex);
	DrawButton(options_pos,options_max,false,false);

	// draw quit button
	glBindTexture(GL_TEXTURE_2D,quit_tex);
	DrawButton(quit_pos,quit_max,false,false);
}

void CMenu::DrawNewGame()
{
	// draw num_players option
	text.Print_NO((int)num_players_pos.x,(int)num_players_pos.y,
		"Spieler pro Team: %d",num_per_team);
	glBindTexture(GL_TEXTURE_2D,arrow_tex);
	DrawButton(dec_players_pos,dec_players_max,false,true);
	DrawButton(inc_players_pos,inc_players_max,false,false);

	// draw map selection
	text.Print_NO((int)maps_pos.x,(int)maps_pos.y,"%s",maps[cur_map]);
	DrawButton(prevmap_pos,prevmap_max,false,true);
	DrawButton(nextmap_pos,nextmap_max,false,false);

	// draw start button
	glBindTexture(GL_TEXTURE_2D,start_tex);
	DrawButton(start_pos,start_max,false,false);

	// draw back button
	glBindTexture(GL_TEXTURE_2D,back_tex);
	DrawButton(back_pos,back_max,false,false);
}

void CMenu::DrawOptions()
{
	// draw switch_shademode option
	text.Print_NO((int)shademode_text.x,(int)shademode_text.y,
		"%s",shademodes[cur_shade]);
	glBindTexture(GL_TEXTURE_2D,shademode_tex);
	DrawButton(switch_shademode_pos,switch_shademode_max,false,false);

	// draw back button
	glBindTexture(GL_TEXTURE_2D,back_tex);
	DrawButton(back_pos,back_max,false,false);
}

void CMenu::DrawButton(point2f &pos,point2f &max,bool inv_x,bool inv_y)
{
	float u[4],v[4];

	if(!inv_x && !inv_y)
	{
		u[0]=0; v[0]=0;
		u[1]=1; v[1]=0;
		u[2]=1; v[2]=1;
		u[3]=0; v[3]=1;
	}
	else if(!inv_x && inv_y)
	{
		u[0]=1; v[0]=0;
		u[1]=0; v[1]=0;
		u[2]=0; v[2]=1;
		u[3]=1; v[3]=1;
	}
	else if(inv_x && !inv_y)
	{
		u[0]=0; v[0]=1;
		u[1]=1; v[1]=1;
		u[2]=1; v[2]=0;
		u[3]=0; v[3]=0;
	}
	else
	{
		u[0]=1; v[0]=1;
		u[1]=0; v[1]=1;
		u[2]=0; v[2]=0;
		u[3]=1; v[3]=0;
	}

	glTranslatef(pos.x,pos.y,0);
	glBegin(GL_QUADS);
	glTexCoord2f(u[0],v[0]);
	glVertex2f(-max.x, max.y);
	glTexCoord2f(u[1],v[1]);
	glVertex2f( max.x, max.y);
	glTexCoord2f(u[2],v[2]);
	glVertex2f( max.x,-max.y);
	glTexCoord2f(u[3],v[3]);
	glVertex2f(-max.x,-max.y);
	glEnd();
	glLoadIdentity();
}

void CMenu::Draw()
{
	if(!active)
		return;

	glDisable(GL_DEPTH_TEST);
	SwitchToOrtho(screen_x,screen_y);

	//DrawDarkShade();

	switch(location)
	{
	case MAIN:
		DrawMain();
		break;

	case NEW_GAME:
		DrawNewGame();
		break;

	case OPTIONS:
		DrawOptions();
		break;
	}

	DrawCursor();

	SwitchBack();
	glEnable(GL_DEPTH_TEST);
	glColor3ub(255,255,255);
}

bool CMenu::FindMaps()
{
	strcpy(maps[0],"test.tri");
	num_maps=1;
	cur_map=0;

	return true;
}

void CMenu::StartNewGame()
{
	main_app.GetGame()->Start(maps[cur_map],num_per_team);

	active=false;
	location=MAIN;
}
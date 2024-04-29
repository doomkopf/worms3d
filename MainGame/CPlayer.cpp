#include "CPlayer.h"
#include "CMain.h"
#include "CShotgun.h"
#include "CGrenadeLauncher.h"
#include "CRocketLauncher.h"
#include "CJetpack.h"
#include "Minigun.h"
#include <gl/glu.h>

extern CMain main_app;

CPlayer::CPlayer()
{
	got_model=false;
	active=false;

	set_standardview=true;
	zoom=false;

	weapon[0] = new CShotgun;
	weapon[1] = new CGrenadeLauncher;
	weapon[2] = new CRocketLauncher;
	weapon[3] = new CJetpack;
	weapon[4] = new CMinigun;
}

void CPlayer::Init(float x,float y,float z)
{
	position.Set(x,y,z);
	destination=position;
	xrot=yrot=0;
	force=0; // kinetic
	force_dir.Set(0,0,0);
	onground=false;
	walking=false;
	last_anim=-1;
	cam_z_pos=0;
	cam_y_pos=0;
	cam_x_rot=0;

	control=main_app.GetControl();
	cam=main_app.GetCamera();

	weapon[0]->has_weapon=true;
	weapon[1]->has_weapon=true;
	weapon[2]->has_weapon=true;
	weapon[3]->has_weapon=true;
	weapon[4]->has_weapon=true;
	weapon[2]->active=true;
	cur_weapon=2;
	health=100;
	dead=false;
}

void CPlayer::MoveFw()
{
	//if(!onground)
		//return;

	destination.xyz[0]-=(float)(SIN(-yrot)*COS(xrot))*speed;
	destination.xyz[2]-=(float)(COS(-yrot)*COS(xrot))*speed;
	//destination.xyz[1]-=(float)SIN(xrot)*speed;

	walking=true;
}

void CPlayer::MoveBw()
{
	//if(!onground)
		//return;

	destination.xyz[0]+=(float)(SIN(-yrot)*COS(xrot))*speed;
	destination.xyz[2]+=(float)(COS(-yrot)*COS(xrot))*speed;
	//destination.xyz[1]+=(float)SIN(xrot)*speed;

	walking=true;
}

void CPlayer::MoveL()
{
	//if(!onground)
		//return;

	destination.xyz[0]-=(float)COS(yrot)*speed;
	destination.xyz[2]-=(float)SIN(yrot)*speed;

	walking=true;
}

void CPlayer::MoveR()
{
	//if(!onground)
		//return;

	destination.xyz[0]+=(float)COS(yrot)*speed;
	destination.xyz[2]+=(float)SIN(yrot)*speed;

	walking=true;
}

void CPlayer::LookX(float m_y)
{
	xrot+=m_y;
	if(xrot>80.0f)
		xrot=80.0f;
	else if(xrot<-80.0f)
		xrot=-80.0f;
}

void CPlayer::TurnY(float m_x)
{
	yrot+=m_x;
}

void CPlayer::Jump()
{
	if(onground)
	{
		force=90;
	}
}

void CPlayer::Update()
{
	CVector3f t;

	if(dead)
		return;

	// calculating looking direction vector
	t=destination;
	t.xyz[0]-=(float)(SIN(-yrot)*COS(xrot))*1000;
	t.xyz[2]-=(float)(COS(-yrot)*COS(xrot))*1000;
	t.xyz[1]-=(float)SIN(xrot)*1000;
	direction=t-destination;
	direction.Normalize();

	// Updating physics
	speed=main_app.frametime*0.1f;
	UpdatePhysics();

	if(walking)
	{
		SetAnimation(RUN);
		walking=false;
	}
	else
		SetAnimation(IDLE1);

	if(extra_force>1)
		SetAnimation(DEATH_FALLBACK);

	if(!active)
		drawmodel=true;

	for(int i=0;i<NUM_WEAPONS;i++)
	{
		if(weapon[i]->has_weapon)
			weapon[i]->Update();
	}

	main_app.GetMap()->ClipDisplacement(this);
	position=destination;
}

void CPlayer::NextWeapon()
{
	weapon[cur_weapon++]->active=false;
	if(cur_weapon>=NUM_WEAPONS)
	{
		cur_weapon=0;
		return;
	}
	while(!weapon[cur_weapon]->has_weapon)
	{
		cur_weapon++;
		if(cur_weapon>=NUM_WEAPONS)
			cur_weapon=0;
	}
}

void CPlayer::Zoom(bool key_down)
{
	GLWindow *win=main_app.GetMainWindow();

	if(key_down)
	{
		if(!zoom)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(15.0f,(float)win->width/(float)win->height,8.0f,16384.0f);
			glMatrixMode(GL_MODELVIEW);
			zoom=true;
		}
	}
	else
	{
		if(zoom)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60.0f,(float)win->width/(float)win->height,8.0f,16384.0f);
			glMatrixMode(GL_MODELVIEW);
			zoom=false;
		}
	}
}

void CPlayer::DrawCrosshair()
{
	if(!main_app.GetMap()->loaded || drawmodel)
		return;

	glColor3ub(255,255,255);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,main_app.GetMainWindow()->width,main_app.GetMainWindow()->height,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(float(main_app.GetMainWindow()->width/2),
		float(main_app.GetMainWindow()->height/2),0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-10,-10);
	glVertex2f( 10,-10);
	glVertex2f( 10, 10);
	glVertex2f(-10, 10);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void CPlayer::DrawStuff()
{
	if(!main_app.GetMap()->loaded)
		return;

	for(int i=0;i<NUM_WEAPONS;i++)
	{
		if(weapon[i]->has_weapon)
			weapon[i]->Draw();
	}

	if(active)
		weapon[cur_weapon]->DrawInterface();
}

void CPlayer::GetInput()
{
	TurnY(control->mouse_x);
	LookX(control->mouse_y);

	if(control->key[FORWARD])
		MoveFw();
	if(control->key[BACKWARD])
		MoveBw();
	if(control->key[LEFT])
		MoveL();
	if(control->key[RIGHT])
		MoveR();
	if(control->key[JUMP])
		Jump();
	if(control->key_d[KEY_MMIDDLE])
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	if(control->hit[NEXT_WEAPON])
		NextWeapon();

	Zoom(control->key_d[KEY_Q]);

	if(control->key[CAM_FAR])
	{
		cam_z_pos+=10;
		cam_y_pos+=2;
		cam_x_rot-=2;
		if(cam_z_pos>100)
		{
			cam_z_pos=100;
			cam_y_pos=20;
			cam_x_rot=-20;
		}
	}
	if(control->key[CAM_NEAR])
	{
		cam_z_pos-=10;
		cam_y_pos-=2;
		cam_x_rot+=2;
		if(cam_z_pos<0 || cam_y_pos<0)
		{
			cam_z_pos=0;
			cam_y_pos=0;
			cam_x_rot=0;
		}
	}

	weapon[cur_weapon]->Shoot(position,direction,control->key[SHOOT]);
}

void CPlayer::SetView()
{
	if(set_standardview)
	{
		if(cam_z_pos==0 && active)
			drawmodel=false;
		else
			drawmodel=true;

		cam->xrot=xrot;
		cam->yrot=yrot;
		cam->position=position;
		cam->Update(0,cam_y_pos,cam_z_pos,cam_x_rot,0,0);
	}
	else
	{
		drawmodel=true;

		//cam->
	}
}

CPlayer::~CPlayer()
{
	for(int i=0;i<NUM_WEAPONS;i++)
		delete weapon[i];
}
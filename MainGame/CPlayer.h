#ifndef CPLAYER
#define CPLAYER

#include "CAnimObject.h"
#include "Camera.h"
#include "CControl.h"
#include "CWeapon.h"

class CPlayer : public CAnimObject
{
public:
	CPlayer();
	~CPlayer();
	void Init(float,float,float);

	void MoveFw();
	void MoveBw();
	void MoveL();
	void MoveR();
	void LookX(float);
	void TurnY(float);
	void Jump();
	void NextWeapon();

	void GetInput();
	void Update();
	void SetView();

	void DrawCrosshair();
	void DrawStuff();

	bool active;
	int cur_weapon;
	//point3f direction; // looking direction
	Camera *cam;

	int health;
	bool dead;
	int team;

protected:
	void Zoom(bool);

	CControl *control;
	CWeapon *weapon[NUM_WEAPONS];
	bool walking,set_standardview;
	bool zoom;
	float cam_z_pos;
	float cam_y_pos;
	float cam_x_rot;
};

#endif
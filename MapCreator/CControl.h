#ifndef CCONTROL
#define CCONTROL

#include "CDirectInput.h"
#include "keys.h"

#define FORWARD 0
#define BACKWARD 1
#define LEFT 2
#define RIGHT 3
#define JUMP 4
#define SHOOT 5
#define MENU 6
#define CAM_NEAR 7
#define CAM_FAR 8
#define NEXT_WEAPON 9
#define SWITCH_CAM 10

#define NUM_ACTIONS 11

class CControl
{
public:
	bool Init();
	void Update();
	bool LoadControlData(char *);

	bool key[NUM_ACTIONS];
	bool hit[NUM_ACTIONS];
	bool key_d[NUM_KEYS];
	bool hit_d[NUM_KEYS];
	float mouse_x,mouse_y;

protected:
	CDirectInput keyboard,mouse;
	char actions[NUM_ACTIONS][32];
	char keys[NUM_KEYS][32];
	unsigned char converts[NUM_KEYS]; // array to convert from direct input key codes
	int identifiers[NUM_KEYS];
	bool c[NUM_ACTIONS];
	bool c_d[NUM_KEYS];
};

#endif
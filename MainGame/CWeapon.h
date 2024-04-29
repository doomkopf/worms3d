#ifndef CWEAPON
#define CWEAPON

#include "defs.h"
#include "math.h"

class CWeapon
{
public:
	CWeapon();
	virtual void Shoot(CVector3f &,CVector3f &,bool) = 0;
	virtual void Update();
	virtual void Draw();
	virtual void DrawInterface();

	bool active,has_weapon;

protected:
};

#endif
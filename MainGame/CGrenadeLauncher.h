#ifndef CGRENADELAUNCHER
#define CGRENADELAUNCHER

#include "CWeapon.h"
#include "CGrenade.h"

class CGrenadeLauncher : public CWeapon
{
public:
	CGrenadeLauncher();
	void Shoot(CVector3f &,CVector3f &,bool);
	void Update();
	void Draw();
	void DrawInterface();

protected:
	float force;
	bool loading,l_inc;
};

#endif
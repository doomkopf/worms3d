#ifndef CROCKETLAUNCHER
#define CROCKETLAUNCHER

#include "CWeapon.h"
#include "CRocket.h"

class CRocketLauncher : public CWeapon
{
public:
	CRocketLauncher();
	void Shoot(CVector3f &,CVector3f &,bool);
	void Update();
	void Draw();

protected:
};

#endif
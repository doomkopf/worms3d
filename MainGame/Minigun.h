#ifndef MINIGUN_H_
#define MINIGUN_H_

#include "CWeapon.h"

class CMinigun : public CWeapon
{
public:
	CMinigun();
	void Shoot(CVector3f &,CVector3f &,bool);
	void Draw();

protected:
	CVector3f start,dir;
	float last_time;
};

#endif
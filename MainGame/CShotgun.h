#ifndef CSHOTGUN
#define CSHOTGUN

#include "CWeapon.h"

class CShotgun : public CWeapon
{
public:
	void Shoot(CVector3f &,CVector3f &,bool);

protected:
};

#endif
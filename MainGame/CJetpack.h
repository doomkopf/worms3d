#ifndef CJETPACK
#define CJETPACK

#include "CWeapon.h"

class CJetpack : public CWeapon
{
public:
	void Shoot(CVector3f &,CVector3f &,bool);

protected:
};

#endif
#ifndef CGRENADE
#define CGRENADE

#include "CStaticObject.h"
#include "CParticleSource.h"

class CGrenade : public CStaticObject
{
public:
	CGrenade();
	void Start(CVector3f &,CVector3f &,float);
	void Update();

protected:
	void DrawExtra();
};

#endif
#ifndef CROCKET
#define CROCKET

#include "CStaticObject.h"

class CRocket : public CStaticObject
{
public:
	CRocket();
	void Start(CVector3f &,CVector3f &);
	void Update();

protected:
};

#endif
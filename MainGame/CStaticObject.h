#ifndef CSTATICOBJECT
#define CSTATICOBJECT

#include "CObject.h"
#include "CModelMS3D.h"

class CStaticObject : public CObject
{
public:
	CStaticObject();
	void SetModel(CModelMS3D *);
	void Draw();

	bool active;

protected:
	virtual void DrawExtra();

	CModelMS3D *model;
	bool got_model;
};

#endif
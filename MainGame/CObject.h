#ifndef COBJECT
#define COBJECT

#include "defs.h"
#include "math.h"

class CObject
{
public:
	virtual void Init(float,float,float);

	virtual void Update() = 0;

	bool onground;
	CVector3f position,destination;
	CVector3f force_dir; // force direction
	float force; // temp
	CVector3f direction; // temp
	float extra_force;
	float xrot,yrot;

protected:
	virtual void UpdatePhysics();

	//float force;
	//float extra_force;
	//point3f direction;
	float speed;
	bool last_og;
};

#endif
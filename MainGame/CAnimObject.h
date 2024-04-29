#ifndef CANIMOBJECT
#define CANIMOBJECT

#include "CObject.h"
#include "CModelMD2.h"

class CAnimObject : public CObject
{
public:
	void SetModel(CModelMD2 *);
	void SetAnimation(int);
	void DrawModel();

protected:
	CModelMD2 *model;
	bool got_model,drawmodel;
	float time;
	int last_anim;
	int frame_start,frame_end,frame_cur;
};

#endif
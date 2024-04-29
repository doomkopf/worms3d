#include "CObject.h"
#include "math.h"
#include "CMain.h"

extern CMain main_app;

#define GRAVITY 1

void CObject::Init(float x,float y,float z)
{
	position.Set(x,y,z);
	destination=position;
	xrot=yrot=0;
	force_dir.Set(0,0,0);
	onground=false;
	extra_force=1;
}

void CObject::UpdatePhysics()
{
	force-=speed*2;

	if(force<-270)
		force=-270;

	if(onground && extra_force<=1)
	{
		//if(extra_force<=1)
		//{
			if(force<0)
			{
				force=-90;
				force_dir.Set(0,0,0);
			}
		//}
	}
	else
	{
		if(last_og && force<0)
		{
			force=0;
		}
		//force_dir.y=0;
		destination+=(force_dir*(speed*extra_force));
	}

	/*point3f t=CrossProduct(Get_upvec(),force_dir);
	//force_dir=Get_upvec();
	VectorRotateAroundVector(force,&force_dir,&t);*/

	destination.xyz[1]-=(0-force)*speed*0.03f;

	extra_force-=speed*0.06f;
	if(extra_force<1)
		extra_force=1;

	last_og=onground;
}

void CObject::Update()
{
	speed=main_app.frametime;
	UpdatePhysics();
}
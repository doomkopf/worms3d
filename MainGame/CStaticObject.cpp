#include "CStaticObject.h"
#include <windows.h>
#include <gl/gl.h>
#include "math.h"

CStaticObject::CStaticObject()
{
	got_model=false;
}

void CStaticObject::SetModel(CModelMS3D *m)
{
	model=m;
	got_model=true;
	active=false;
}

void CStaticObject::Draw()
{
	CVector3f vec;
	float angle;

	DrawExtra();

	if(!got_model || !active)
		return;

	vec=CrossProduct(CVector3f(0,1,0),direction);
	vec.Normalize();
	angle=acosf(DotProduct(CVector3f(0,1,0),direction))*PIUNDER180;

	glPushMatrix();

	glTranslatef(position.xyz[0],position.xyz[1],position.xyz[2]);

	glRotatef(angle,vec.xyz[0],vec.xyz[1],vec.xyz[2]);
	glRotatef(90,1,0,0);

	glColor3ub(50,50,50);
	model->Draw();

	glPopMatrix();
}

void CStaticObject::DrawExtra()
{
}
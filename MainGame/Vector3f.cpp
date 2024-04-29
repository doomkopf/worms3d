#include "Vector3f.h"
#include "math.h"

CVector3f::CVector3f(float fx,float fy,float fz)
{
	xyz[0]=fx;
	xyz[1]=fy;
	xyz[2]=fz;
}

void CVector3f::Set(float fx,float fy,float fz)
{
	xyz[0]=fx;
	xyz[1]=fy;
	xyz[2]=fz;
}

void CVector3f::Inverse()
{
	xyz[0]=-xyz[0];
	xyz[1]=-xyz[1];
	xyz[2]=-xyz[2];
}

CVector3f CVector3f::operator +(const CVector3f &add) const
{
	return CVector3f(xyz[0]+add.xyz[0],
		xyz[1]+add.xyz[1],
		xyz[2]+add.xyz[2]);
}

CVector3f CVector3f::operator -(const CVector3f &sub) const
{
	return CVector3f(xyz[0]-sub.xyz[0],
		xyz[1]-sub.xyz[1],
		xyz[2]-sub.xyz[2]);
}

CVector3f CVector3f::operator *(float scale) const
{
	return CVector3f(xyz[0]*scale,
		xyz[1]*scale,
		xyz[2]*scale);
}

CVector3f CVector3f::operator /(float div) const
{
	float scale=1/div;

	return CVector3f(xyz[0]*scale,
		xyz[1]*scale,
		xyz[2]*scale);
}

void CVector3f::operator +=(const CVector3f &add)
{
	xyz[0]+=add.xyz[0];
	xyz[1]+=add.xyz[1];
	xyz[2]+=add.xyz[2];
}

void CVector3f::operator -=(const CVector3f &sub)
{
	xyz[0]-=sub.xyz[0];
	xyz[1]-=sub.xyz[1];
	xyz[2]-=sub.xyz[2];
}

void CVector3f::operator *=(float scale)
{
	xyz[0]*=scale;
	xyz[1]*=scale;
	xyz[2]*=scale;
}

void CVector3f::operator /=(float div)
{
	float scale=1/div;

	xyz[0]*=scale;
	xyz[1]*=scale;
	xyz[2]*=scale;
}
/*
float CVector3f::DotProduct(const CVector3f &vec) const
{
	return ((xyz[0]*vec.xyz[0]) + (xyz[1]*vec.xyz[1]) + (xyz[2]*vec.xyz[2]));
}

CVector3f CVector3f::CrossProduct(const CVector3f &vec) const
{
	CVector3f t=*this;

	t.xyz[0]=(xyz[1]*vec.xyz[2])-(xyz[2]*vec.xyz[1]);
	t.xyz[1]=(xyz[2]*vec.xyz[0])-(xyz[0]*vec.xyz[2]);
	t.xyz[2]=(xyz[0]*vec.xyz[1])-(xyz[1]*vec.xyz[0]);

	return t;
}

void CVector3f::Cross(const CVector3f &vec)
{
	CVector3f t=*this;

	xyz[0]=(t.xyz[1]*vec.xyz[2])-(t.xyz[2]*vec.xyz[1]);
	xyz[1]=(t.xyz[2]*vec.xyz[0])-(t.xyz[0]*vec.xyz[2]);
	xyz[2]=(t.xyz[0]*vec.xyz[1])-(t.xyz[1]*vec.xyz[0]);
}
*/
float CVector3f::Length() const
{
	//return sqrtf(DotProduct(*this));
	return sqrtf((xyz[0]*xyz[0]) + (xyz[1]*xyz[1]) + (xyz[2]*xyz[2]));
}

void CVector3f::Normalize()
{
	float l=1/Length();

	xyz[0]*=l;
	xyz[1]*=l;
	xyz[2]*=l;
}
#include "math.h"

#define SIN(f) (sin(f*PIOVER180))
#define COS(f) (cos(f*PIOVER180))

float DotProduct(point3f v1,point3f v2)
{
	return ((v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z));
}

point3f CrossProduct(point3f v1,point3f v2)
{
	point3f v;

	v.x=(v1.y*v2.z)-(v1.z*v2.y);
	v.y=(v1.z*v2.x)-(v1.x*v2.z);
	v.z=(v1.x*v2.y)-(v1.y*v2.x);

	return v;
}

point3f VectorAdd(point3f v1,point3f v2)
{
	point3f v;

	v.x=v1.x+v2.x;
	v.y=v1.y+v2.y;
	v.z=v1.z+v2.z;

	return v;
}

point3f VectorSubtract(point3f v1,point3f v2)
{
	point3f v;

	v.x=v1.x-v2.x;
	v.y=v1.y-v2.y;
	v.z=v1.z-v2.z;

	return v;
}

void VectorScale(point3f *v,float scalar,bool inc)
{
	if(!inc)
		scalar=1/scalar;

	v->x*=scalar;
	v->y*=scalar;
	v->z*=scalar;
}

point3f VectorScale(point3f v,float scalar,bool inc)
{
	point3f v1;

	if(!inc)
		scalar=1/scalar;

	v1.x=v.x*scalar;
	v1.y=v.y*scalar;
	v1.z=v.z*scalar;

	return v1;
}

float VectorLength(point3f v)
{
	return (sqrtf(DotProduct(v,v)));
}

void VectorNormalize(point3f *v)
{
	float length=1/VectorLength(*v);
	v->x*=length;
	v->y*=length;
	v->z*=length;
}

point3f VectorNormalize(point3f v)
{
	float length=1/VectorLength(v);
	v.x*=length;
	v.y*=length;
	v.z*=length;

	return v;
}

void MatrixConcatenate(float *result, float *ma, float *mb)
{
	int i;
	double mb00, mb01, mb02, mb03, mb10, mb11, mb12, mb13, mb20, mb21, mb22, mb23, mb30, mb31, mb32, mb33;
    double mai0, mai1, mai2, mai3;
	mb00 = mb[0];  mb01 = mb[1];
	mb02 = mb[2];  mb03 = mb[3];
	mb10 = mb[4];  mb11 = mb[5];
	mb12 = mb[6];  mb13 = mb[7];
	mb20 = mb[8];  mb21 = mb[9];
	mb22 = mb[10];  mb23 = mb[11];
	mb30 = mb[12];  mb31 = mb[13];
	mb32 = mb[14];  mb33 = mb[15];
	for (i = 0; i < 4; i++)
	{
		mai0 = ma[i*4+0];  mai1 = ma[i*4+1];
		mai2 = ma[i*4+2];  mai3 = ma[i*4+3];
		result[i*4+0] = float(mai0 * mb00 + mai1 * mb10 + mai2 * mb20 + mai3 * mb30);
		result[i*4+1] = float(mai0 * mb01 + mai1 * mb11 + mai2 * mb21 + mai3 * mb31);
		result[i*4+2] = float(mai0 * mb02 + mai1 * mb12 + mai2 * mb22 + mai3 * mb32);
		result[i*4+3] = float(mai0 * mb03 + mai1 * mb13 + mai2 * mb23 + mai3 * mb33);
	}
}

float abs_f(float f)
{
	if(f<0)
		return -f;

	return f;
}

void abs_f(float *f)
{
	if(*f<0)
		*f*=-1;
}

void swap(int *a,int *b)
{
	int t=*a;
	*a=*b;
	*b=t;
}

void swap(short *a,short *b)
{
	short t=*a;
	*a=*b;
	*b=t;
}

void swap(float *a,float *b)
{
	float t=*a;
	*a=*b;
	*b=t;
}

void VectorRotateX(float degrees,point3f *v)
{
	float bak=v->y;
	degrees*=PIOVER180;

	v->y = (v->y*cosf(degrees)) - (v->z*sinf(degrees));
	v->z = (v->z*cosf(degrees)) + (bak*sinf(degrees));
}

void VectorRotateY(float degrees,point3f *v)
{
	float bak=v->z;
	degrees*=PIOVER180;

	v->z = (v->z*cosf(degrees)) - (v->x*sinf(degrees));
	v->x = (v->x*cosf(degrees)) + (bak*sinf(degrees));
}

void VectorRotateZ(float degrees,point3f *v)
{
	float bak=v->x;
	degrees*=PIOVER180;

	v->x = (v->x*cosf(degrees)) - (v->y*sinf(degrees));
	v->y = (v->y*cosf(degrees)) + (bak*sinf(degrees));
}

point3f VectorRotateX(float degrees,point3f v)
{
	point3f v_new;
	degrees*=PIOVER180;

	v_new.y = (v.y*cosf(degrees)) - (v.z*sinf(degrees));
	v_new.z = (v.z*cosf(degrees)) + (v.y*sinf(degrees));
	v_new.x = v.x;

	return v_new;
}

point3f VectorRotateY(float degrees,point3f v)
{
	point3f v_new;
	degrees*=PIOVER180;

	v_new.z = (v.z*cosf(degrees)) - (v.x*sinf(degrees));
	v_new.x = (v.x*cosf(degrees)) + (v.z*sinf(degrees));
	v_new.y = v.y;

	return v_new;
}

point3f VectorRotateZ(float degrees,point3f v)
{
	point3f v_new;
	degrees*=PIOVER180;

	v_new.x = (v.x*cosf(degrees)) - (v.y*sinf(degrees));
	v_new.y = (v.y*cosf(degrees)) + (v.x*sinf(degrees));
	v_new.z = v.z;

	return v_new;
}

bool GetIntersectionPoint_ray_plane(point3f ray_origin,point3f ray_v,Plane plane,point3f *intersection)
{
	float cosa,t;
	cosa=DotProduct(plane.normal,ray_v);
	if(cosa==0)
		return false;

	t=-(DotProduct(plane.normal,ray_origin)+plane.distance)/cosa;
	VectorScale(&ray_v,t,true);
	*intersection=VectorAdd(ray_origin,ray_v);

	return true;
}

float GetDistance_pp(point3f p1,point3f p2)
{
	return (VectorLength(VectorSubtract(p1,p2)));
}

float GetAngle_vv(point3f v1,point3f v2)
{
	return ( acosf(DotProduct(v1,v2))*PIUNDER180 );
}

point3f CalcNormal(point3f *vertex,int num_vertices)
{
	point3f v1,v2;

	v1=VectorSubtract(vertex[1],vertex[0]);
	v2=VectorSubtract(vertex[num_vertices-1],vertex[0]);

	v1=CrossProduct(v1,v2);
	VectorNormalize(&v1);

	return v1;
}

Plane CalcPlane(point3f *vertex,int num_vertices)
{
	Plane plane;

	plane.normal=CalcNormal(vertex,num_vertices);
	plane.distance=-DotProduct(plane.normal,vertex[0]);

	return plane;
}

void IdentityMatrix(float matrix[3][3])
{
	matrix[0][0]=1;
	matrix[0][1]=0;
	matrix[0][2]=0;
	matrix[1][0]=0;
	matrix[1][1]=1;
	matrix[1][2]=0;
	matrix[2][0]=0;
	matrix[2][1]=0;
	matrix[2][2]=1;
}

void TransposeMatrix(float matrix[3][3])
{
	swap(&matrix[0][1],&matrix[1][0]);
	swap(&matrix[0][2],&matrix[2][0]);
	swap(&matrix[1][2],&matrix[2][1]);
}

void RotatePoint(point3f *p,float m[3][3])
{
	point3f pc=*p;
	p->x = pc.x * m[0][0] + pc.y * m[1][0] + pc.z * m[2][0];
	p->y = pc.x * m[0][1] + pc.y * m[1][1] + pc.z * m[2][1];
	p->z = pc.x * m[0][2] + pc.y * m[1][2] + pc.z * m[2][2];
}

point3f RotatePoint(point3f p,float m[3][3])
{
	point3f pc=p;
	p.x = pc.x * m[0][0] + pc.y * m[1][0] + pc.z * m[2][0];
	p.y = pc.x * m[0][1] + pc.y * m[1][1] + pc.z * m[2][1];
	p.z = pc.x * m[0][2] + pc.y * m[1][2] + pc.z * m[2][2];

	return p;
}

void RotateMatrix(float m[3][3],float x_deg,float y_deg,float z_deg)
{
	m[0][0] = (COS(y_deg)*COS(z_deg)) + (SIN(z_deg)*SIN(y_deg)*SIN(x_deg));
	m[0][1] = (COS(x_deg)*SIN(z_deg));
	m[0][2] =-(COS(z_deg)*SIN(y_deg)) + (COS(y_deg)*SIN(x_deg)*SIN(z_deg));
	m[1][0] =-(COS(y_deg)*SIN(z_deg)) + (COS(z_deg)*SIN(y_deg)*SIN(x_deg));
	m[1][1] = (COS(x_deg)*COS(z_deg));
	m[1][2] = (SIN(y_deg)*SIN(z_deg)) + (COS(y_deg)*COS(z_deg)*SIN(x_deg));
	m[2][0] = (COS(x_deg)*SIN(y_deg));
	m[2][1] =-SIN(x_deg);
	m[2][2] = (COS(y_deg)*COS(x_deg));
}

void RotateX(float m[3][3],float deg)
{
	m[1][1]=COS(deg);
	m[1][2]=SIN(deg);
	m[2][1]=-SIN(deg);
	m[2][2]=m[1][1];
}

void RotateY(float m[3][3],float deg)
{
	m[0][0]=COS(deg);
	m[0][2]=-SIN(deg);
	m[2][0]=-m[0][2];
	m[2][2]=m[0][0];
}

void RotateZ(float m[3][3],float deg)
{
	m[0][0]=COS(deg);
	m[0][1]=SIN(deg);
	m[1][0]=-m[0][1];
	m[1][1]=m[0][0];
}

void CalcRotationMatrix(point3f *vertex,int num_vertices,float matrix[3][3])
{
	point3f v1,v2,v3;

	v1=VectorSubtract(vertex[1],vertex[0]);
	v2=VectorSubtract(vertex[num_vertices-1],vertex[0]);
	v3=CrossProduct(v1,v2);
	v2=CrossProduct(v1,v3);

	VectorNormalize(&v1);
	VectorNormalize(&v2);
	VectorNormalize(&v3);

	matrix[0][0]=v1.x;
	matrix[0][1]=v1.y;
	matrix[0][2]=v1.z;
	matrix[1][0]=v2.x;
	matrix[1][1]=v2.y;
	matrix[1][2]=v2.z;
	matrix[2][0]=v3.x;
	matrix[2][1]=v3.y;
	matrix[2][2]=v3.z;
}
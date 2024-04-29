#ifndef MATH_STUFF
#define MATH_STUFF

#include <math.h>
#include "Vector3f.h"

#define PI 3.1415926535897932384626433832795f
#define PIOVER180 0.0174532925199432957692369076848861f
#define PIUNDER180 57.2957795130823208767981548141052f

#define SIN(f) (sinf(f*PIOVER180))
#define COS(f) (cosf(f*PIOVER180))

#define FRONT 0
#define BACK 1
#define COPLANAR 2
#define SPANNING 3

typedef struct
{
	CVector3f normal;
	float distance;
} Plane;

float DotProduct(const CVector3f &,const CVector3f &);
CVector3f CrossProduct(const CVector3f &,const CVector3f &);
CVector3f VectorAdd(CVector3f,const CVector3f &);
CVector3f VectorSubtract(CVector3f,const CVector3f &);
void VectorScale(CVector3f *,float,bool);
CVector3f VectorScale(CVector3f,float,bool);
float VectorLength(const CVector3f &);
void VectorNormalize(CVector3f *);
CVector3f VectorNormalize(CVector3f);
void MatrixConcatenate(float *, float *, float *);
float abs_f(const float &);
void abs_f(float *);
void swap(int *,int*);
void swap(short *,short *);
void swap(float *,float *);
void swap(unsigned char *,unsigned char *);
void VectorRotateX(float,CVector3f *);
void VectorRotateY(float,CVector3f *);
void VectorRotateZ(float,CVector3f *);
CVector3f VectorRotateX(float,const CVector3f &);
CVector3f VectorRotateY(float,const CVector3f &);
CVector3f VectorRotateZ(float,const CVector3f &);
bool GetIntersectionPoint_ray_plane(const CVector3f &,CVector3f,const Plane &,CVector3f *);
bool GetIntersectionPoint_lineseg_plane(const CVector3f &,const CVector3f &,const Plane &,CVector3f *);
bool GetIntersectionPoint_3plane(const Plane &,const Plane &,const Plane &,CVector3f *);
float GetDistance_pp(const CVector3f &,const CVector3f &);
float GetDistance_ray_point(const CVector3f &,const CVector3f &,const CVector3f &);
float GetAngle_vv(const CVector3f &,const CVector3f &);
CVector3f CalcNormal(CVector3f *);
Plane CalcPlane(CVector3f *);
void VectorRotateAroundVector(const float &,CVector3f *,const CVector3f &);

int ClassifyPolygon(CVertex3f *,const int &,const Plane &,float epsilon=0);
void SplitPolygon(CVertex3f *,
				  const int &,
				  const Plane &,
				  CVertex3f *,
				  int *,
				  CVertex3f *,
				  int *);

void IdentityMatrix(float [3][3]);
void TransposeMatrix(float [3][3]);
void RotatePoint(CVector3f *,float [3][3]);
CVector3f RotatePoint(const CVector3f &,float [3][3]);
void RotateMatrix(float [3][3],const float &,const float &,const float &);
void RotateX(float [3][3],const float &);
void RotateY(float [3][3],const float &);
void RotateZ(float [3][3],const float &);
void CalcRotationMatrix(CVector3f *,const int &,float [3][3]);

#endif
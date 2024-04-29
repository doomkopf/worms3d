#include <math.h>
#include "defs.h"

#define PI 3.1415926535897932384626433832795f
#define PIOVER180 0.0174532925199432957692369076848861f
#define PIUNDER180 57.2957795130823208767981548141052f

float DotProduct(point3f,point3f);
point3f CrossProduct(point3f,point3f);
point3f VectorAdd(point3f,point3f);
point3f VectorSubtract(point3f,point3f);
void VectorScale(point3f *,float,bool);
point3f VectorScale(point3f,float,bool);
float VectorLength(point3f);
void VectorNormalize(point3f *);
point3f VectorNormalize(point3f);
void MatrixConcatenate(float *, float *, float *);
float abs_f(float);
void abs_f(float *);
void swap(int *,int *);
void swap(short *,short *);
void swap(float *,float *);
void VectorRotateX(float,point3f *);
void VectorRotateY(float,point3f *);
void VectorRotateZ(float,point3f *);
point3f VectorRotateX(float,point3f);
point3f VectorRotateY(float,point3f);
point3f VectorRotateZ(float,point3f);
bool GetIntersectionPoint_ray_plane(point3f,point3f,Plane,point3f *);
float GetDistance_pp(point3f,point3f);
float GetAngle_vv(point3f,point3f);
point3f CalcNormal(point3f *,int);
Plane CalcPlane(point3f *,int);

void IdentityMatrix(float [3][3]);
void TransposeMatrix(float [3][3]);
void RotatePoint(point3f *,float [3][3]);
point3f RotatePoint(point3f,float [3][3]);
void RotateMatrix(float [3][3],float,float,float);
void RotateX(float [3][3],float);
void RotateY(float [3][3],float);
void RotateZ(float [3][3],float);
void CalcRotationMatrix(point3f *,int,float [3][3]);
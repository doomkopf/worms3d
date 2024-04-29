#include "math.h"

float DotProduct(const CVector3f &v1,const CVector3f &v2)
{
	return ((v1.xyz[0]*v2.xyz[0]) + (v1.xyz[1]*v2.xyz[1]) + (v1.xyz[2]*v2.xyz[2]));
}

CVector3f CrossProduct(const CVector3f &v1,const CVector3f &v2)
{
	CVector3f v;

	v.xyz[0]=(v1.xyz[1]*v2.xyz[2])-(v1.xyz[2]*v2.xyz[1]);
	v.xyz[1]=(v1.xyz[2]*v2.xyz[0])-(v1.xyz[0]*v2.xyz[2]);
	v.xyz[2]=(v1.xyz[0]*v2.xyz[1])-(v1.xyz[1]*v2.xyz[0]);

	return v;
}

CVector3f VectorAdd(CVector3f v1,const CVector3f &v2)
{
	v1.xyz[0]+=v2.xyz[0];
	v1.xyz[1]+=v2.xyz[1];
	v1.xyz[2]+=v2.xyz[2];

	return v1;
}

CVector3f VectorSubtract(CVector3f v1,const CVector3f &v2)
{
	v1.xyz[0]-=v2.xyz[0];
	v1.xyz[1]-=v2.xyz[1];
	v1.xyz[2]-=v2.xyz[2];

	return v1;
}

void VectorScale(CVector3f *v,float scalar,bool inc)
{
	if(!inc)
		scalar=1/scalar;

	v->xyz[0]*=scalar;
	v->xyz[1]*=scalar;
	v->xyz[2]*=scalar;
}

CVector3f VectorScale(CVector3f v,float scalar,bool inc)
{
	if(!inc)
		scalar=1/scalar;

	v.xyz[0]*=scalar;
	v.xyz[1]*=scalar;
	v.xyz[2]*=scalar;

	return v;
}

float VectorLength(const CVector3f &v)
{
	return (sqrtf(DotProduct(v,v)));
}

void VectorNormalize(CVector3f *v)
{
	float length=1/VectorLength(*v);
	v->xyz[0]*=length;
	v->xyz[1]*=length;
	v->xyz[2]*=length;
}

CVector3f VectorNormalize(CVector3f v)
{
	float length=1/VectorLength(v);
	v.xyz[0]*=length;
	v.xyz[1]*=length;
	v.xyz[2]*=length;

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

float abs_f(const float &f)
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

void swap(unsigned char *a,unsigned char *b)
{
	unsigned char t=*a;
	*a=*b;
	*b=t;
}

void VectorRotateX(float degrees,CVector3f *v)
{
	float bak=v->xyz[1];
	degrees*=PIOVER180;

	v->xyz[1] = (v->xyz[1]*cosf(degrees)) - (v->xyz[2]*sinf(degrees));
	v->xyz[2] = (v->xyz[2]*cosf(degrees)) + (bak*sinf(degrees));
}

void VectorRotateY(float degrees,CVector3f *v)
{
	float bak=v->xyz[2];
	degrees*=PIOVER180;

	v->xyz[2] = (v->xyz[2]*cosf(degrees)) - (v->xyz[0]*sinf(degrees));
	v->xyz[0] = (v->xyz[0]*cosf(degrees)) + (bak*sinf(degrees));
}

void VectorRotateZ(float degrees,CVector3f *v)
{
	float bak=v->xyz[0];
	degrees*=PIOVER180;

	v->xyz[0] = (v->xyz[0]*cosf(degrees)) - (v->xyz[1]*sinf(degrees));
	v->xyz[1] = (v->xyz[1]*cosf(degrees)) + (bak*sinf(degrees));
}

CVector3f VectorRotateX(float degrees,const CVector3f &v)
{
	CVector3f v_new;
	degrees*=PIOVER180;

	v_new.xyz[1] = (v.xyz[1]*cosf(degrees)) - (v.xyz[2]*sinf(degrees));
	v_new.xyz[2] = (v.xyz[2]*cosf(degrees)) + (v.xyz[1]*sinf(degrees));
	v_new.xyz[0] = v.xyz[0];

	return v_new;
}

CVector3f VectorRotateY(float degrees,const CVector3f &v)
{
	CVector3f v_new;
	degrees*=PIOVER180;

	v_new.xyz[2] = (v.xyz[2]*cosf(degrees)) - (v.xyz[0]*sinf(degrees));
	v_new.xyz[0] = (v.xyz[0]*cosf(degrees)) + (v.xyz[2]*sinf(degrees));
	v_new.xyz[1] = v.xyz[1];

	return v_new;
}

CVector3f VectorRotateZ(float degrees,const CVector3f &v)
{
	CVector3f v_new;
	degrees*=PIOVER180;

	v_new.xyz[0] = (v.xyz[0]*cosf(degrees)) - (v.xyz[1]*sinf(degrees));
	v_new.xyz[1] = (v.xyz[1]*cosf(degrees)) + (v.xyz[0]*sinf(degrees));
	v_new.xyz[2] = v.xyz[2];

	return v_new;
}

bool GetIntersectionPoint_ray_plane(const CVector3f &ray_origin,CVector3f ray_v,const Plane &plane,CVector3f *intersection)
{
	float cosa,t;
	cosa=DotProduct(plane.normal,ray_v);
	if(cosa>=0)
		return false;

	t=-(DotProduct(plane.normal,ray_origin)+plane.distance) / cosa;
	ray_v*=t;
	*intersection=ray_origin+ray_v;

	return true;
}

bool GetIntersectionPoint_lineseg_plane(const CVector3f &p1,const CVector3f &p2,const Plane &plane,CVector3f *intersection)
{
	float denom;

	CVector3f d;
	d=p1-p2;
	d.Normalize();
	denom=DotProduct(plane.normal,d);

	if(denom<=0)
		return false;

	float p=-(DotProduct(plane.normal,p1)+plane.distance) / denom;

	d*=p;
	*intersection=p1+d;

	return true;
}

bool GetIntersectionPoint_3plane(const Plane &p1,const Plane &p2,const Plane &p3,CVector3f *p)
{
	float denom=DotProduct(p1.normal,CrossProduct(p2.normal,p3.normal));
	if(denom==0)
		return false;

	*p=((CrossProduct(p2.normal,p3.normal)*(-p1.distance))+
		(CrossProduct(p3.normal,p1.normal)*(-p2.distance))+
		(CrossProduct(p1.normal,p2.normal)*(-p3.distance)))/denom;

	return true;
}

float GetDistance_pp(const CVector3f &p1,const CVector3f &p2)
{
	//return (VectorLength(p1-p2));
	return (p1-p2).Length();
}

float GetDistance_ray_point(const CVector3f &ray_orig,const CVector3f &ray_vec,const CVector3f &p)
{
	CVector3f v;
	Plane plane;
	float dist;

	v=VectorSubtract(p,ray_orig);
	if(DotProduct(VectorNormalize(v),ray_vec)<=0)
	{
		dist=VectorLength(v);
		return dist;
	}

	v=CrossProduct(v,ray_vec);
	VectorNormalize(&v);

	plane.normal=CrossProduct(v,ray_vec);
	plane.distance=-DotProduct(plane.normal,ray_orig);
	dist=DotProduct(plane.normal,p)+plane.distance;

	return abs_f(dist);
}

float GetAngle_vv(const CVector3f &v1,const CVector3f &v2)
{
	return ( acosf(DotProduct(v1,v2))*PIUNDER180 );
}

CVector3f CalcNormal(CVector3f *vertex)
{
	CVector3f v1,v2;

	v1=VectorSubtract(vertex[1],vertex[0]);
	v2=VectorSubtract(vertex[2],vertex[0]);

	v1=CrossProduct(v1,v2);
	VectorNormalize(&v1);

	return v1;
}

Plane CalcPlane(CVector3f *vertex)
{
	Plane plane;

	plane.normal=CalcNormal(vertex);
	plane.distance=-DotProduct(plane.normal,vertex[0]);

	return plane;
}

void VectorRotateAroundVector(const float &angle,CVector3f *v,const CVector3f &axis)
{
	float matrix[3][3];
	float c,s;

	c=COS(angle);
	s=SIN(angle);

	matrix[0][0]=(axis.xyz[0]*axis.xyz[0])*(1.0f-c)+c;
	matrix[0][1]=(axis.xyz[1]*axis.xyz[0])*(1.0f-c)+(axis.xyz[2]*s);
	matrix[0][2]=(axis.xyz[2]*axis.xyz[0])*(1.0f-c)-(axis.xyz[1]*s);
	matrix[1][0]=(axis.xyz[0]*axis.xyz[1])*(1.0f-c)-(axis.xyz[2]*s);
	matrix[1][1]=(axis.xyz[1]*axis.xyz[1])*(1.0f-c)+c;
	matrix[1][2]=(axis.xyz[2]*axis.xyz[1])*(1.0f-c)+(axis.xyz[0]*s);
	matrix[2][0]=(axis.xyz[0]*axis.xyz[2])*(1.0f-c)+(axis.xyz[1]*s);
	matrix[2][1]=(axis.xyz[1]*axis.xyz[2])*(1.0f-c)-(axis.xyz[0]*s);
	matrix[2][2]=(axis.xyz[2]*axis.xyz[2])*(1.0f-c)+c;

	RotatePoint(v,matrix);
}

int ClassifyPolygon(CVertex3f *vertex,const int &num_vertices,const Plane &plane,float epsilon)
{
	int front,back,coplanar;

	front=back=coplanar=0;

	for(int i=0;i<num_vertices;i++)
	{
		if(DotProduct(plane.normal,vertex[i].v)+plane.distance>epsilon)
			front++;
		else if(DotProduct(plane.normal,vertex[i].v)+plane.distance<epsilon)
			back++;
		else
			coplanar++;
	}

	if(coplanar == num_vertices)
		return COPLANAR;
	if(front+coplanar == num_vertices)
		return FRONT;
	if(back+coplanar == num_vertices)
		return BACK;

	return SPANNING;
}

void SplitPolygon(CVertex3f *vertex,
				  const int &num_v,
				  const Plane &plane,
				  CVertex3f *vertex_p1,
				  int *n_v1,
				  CVertex3f *vertex_p2,
				  int *n_v2)
{
	float d1,d2;
	CVertex3f v_new;
	int num_v1,num_v2;
	num_v1=num_v2=0;

	for(int i=0,j;i<num_v;i++)
	{
		d1=DotProduct(vertex[i].v,plane.normal)+plane.distance;
		if(i==num_v-1)
			j=0;
		else
			j=i+1;
		d2=DotProduct(vertex[j].v,plane.normal)+plane.distance;

		if(d1>0 && d2<0) // v1=front v2=back
		{
			// adding new vertex to both polys
			GetIntersectionPoint_lineseg_plane(vertex[i].v,
				vertex[j].v,
				plane,
				&v_new.v);
			float l1=(vertex[j].v-vertex[i].v).Length();
			float l2=(v_new.v-vertex[i].v).Length();
			float percent=l2/l1;
			float deltax=vertex[j].tu-vertex[i].tu;
			float deltay=vertex[j].tv-vertex[i].tv;
			v_new.tu=vertex[i].tu+(deltax*percent);
			v_new.tv=vertex[i].tv+(deltay*percent);
			vertex_p1[num_v1++]=v_new;
			vertex_p2[num_v2++]=v_new;

			// adding v2 to back poly
			vertex_p2[num_v2++]=vertex[j];
		}
		else if(d1<0 && d2>0) // v1=back v2=front
		{
			// adding new vertex to both polys
			GetIntersectionPoint_lineseg_plane(vertex[j].v,
				vertex[i].v,
				plane,
				&v_new.v);
			float l1=(vertex[j].v-vertex[i].v).Length();
			float l2=(v_new.v-vertex[i].v).Length();
			float percent=l2/l1;
			float deltax=vertex[j].tu-vertex[i].tu;
			float deltay=vertex[j].tv-vertex[i].tv;
			v_new.tu=vertex[i].tu+(deltax*percent);
			v_new.tv=vertex[i].tv+(deltay*percent);
			vertex_p1[num_v1++]=v_new;
			vertex_p2[num_v2++]=v_new;

			// adding v2 to front poly
			vertex_p1[num_v1++]=vertex[j];
		}
		else if(d1<0 && d2==0) // v1=back v2=onplane
		{
			// adding v2 to both
			vertex_p1[num_v1++]=vertex[j];
			vertex_p2[num_v2++]=vertex[j];
		}
		else if(d1>0 && d2==0) // v1=front v2==onplane
		{
			// adding v2 to both
			vertex_p1[num_v1++]=vertex[j];
			vertex_p2[num_v2++]=vertex[j];
		}
		else if(d1==0 && d2>0) // v1=onplane v2=front
		{
			// adding v2 to front poly
			vertex_p1[num_v1++]=vertex[j];
		}
		else if(d1==0 && d2<0) // v1=onplane v2=back
		{
			// adding v2 to back poly
			vertex_p2[num_v2++]=vertex[j];
		}
		else if(d1>0 && d2>0) // v1=front v2=front
		{
			// adding v2 to front poly
			vertex_p1[num_v1++]=vertex[j];
		}
		else // v1=back v2=back
		{
			// adding v2 to back poly
			vertex_p2[num_v2++]=vertex[j];
		}
	}
	*n_v1=num_v1;
	*n_v2=num_v2;
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

void RotatePoint(CVector3f *p,float m[3][3])
{
	CVector3f pc=*p;
	p->xyz[0] = pc.xyz[0] * m[0][0] + pc.xyz[1] * m[1][0] + pc.xyz[2] * m[2][0];
	p->xyz[1] = pc.xyz[0] * m[0][1] + pc.xyz[1] * m[1][1] + pc.xyz[2] * m[2][1];
	p->xyz[2] = pc.xyz[0] * m[0][2] + pc.xyz[1] * m[1][2] + pc.xyz[2] * m[2][2];
}

CVector3f RotatePoint(const CVector3f &p,float m[3][3])
{
	CVector3f pc=p;
	pc.xyz[0] = p.xyz[0] * m[0][0] + p.xyz[1] * m[1][0] + p.xyz[2] * m[2][0];
	pc.xyz[1] = p.xyz[0] * m[0][1] + p.xyz[1] * m[1][1] + p.xyz[2] * m[2][1];
	pc.xyz[2] = p.xyz[0] * m[0][2] + p.xyz[1] * m[1][2] + p.xyz[2] * m[2][2];

	return pc;
}

void RotateMatrix(float m[3][3],const float &x_deg,const float &y_deg,const float &z_deg)
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

void RotateX(float m[3][3],const float &deg)
{
	m[1][1]=COS(deg);
	m[1][2]=SIN(deg);
	m[2][1]=-SIN(deg);
	m[2][2]=m[1][1];
}

void RotateY(float m[3][3],const float &deg)
{
	m[0][0]=COS(deg);
	m[0][2]=-SIN(deg);
	m[2][0]=-m[0][2];
	m[2][2]=m[0][0];
}

void RotateZ(float m[3][3],const float &deg)
{
	m[0][0]=COS(deg);
	m[0][1]=SIN(deg);
	m[1][0]=-m[0][1];
	m[1][1]=m[0][0];
}

void CalcRotationMatrix(CVector3f *vertex,const int &num_vertices,float matrix[3][3])
{
	CVector3f v1,v2,v3;

	v1=VectorSubtract(vertex[1],vertex[0]);
	v2=VectorSubtract(vertex[num_vertices-1],vertex[0]);
	v3=CrossProduct(v1,v2);
	v2=CrossProduct(v1,v3);

	VectorNormalize(&v1);
	VectorNormalize(&v2);
	VectorNormalize(&v3);

	matrix[0][0]=v1.xyz[0];
	matrix[0][1]=v1.xyz[1];
	matrix[0][2]=v1.xyz[2];
	matrix[1][0]=v2.xyz[0];
	matrix[1][1]=v2.xyz[1];
	matrix[1][2]=v2.xyz[2];
	matrix[2][0]=v3.xyz[0];
	matrix[2][1]=v3.xyz[1];
	matrix[2][2]=v3.xyz[2];
}
#include "Camera.h"
#include <windows.h>
#include <gl/gl.h>

void Camera::Init(float x,float y,float z)
{
	position.Set(x,y,z);
}

void Camera::Update(float pos_x,float pos_y,float pos_z,float rot_x,float rot_y,float rot_z)
{
	glLoadIdentity();

	glRotatef(xrot-rot_x,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glGetDoublev(GL_MODELVIEW_MATRIX,temp_matrix);

	glLoadIdentity();
	glTranslatef(-pos_x,-pos_y,-pos_z);
	glRotatef(xrot-rot_x,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glTranslatef(-position.xyz[0],-position.xyz[1],-position.xyz[2]);
	glPushMatrix();

	CalcViewFrustumPlanes();
}

void Camera::Update()
{
	glLoadIdentity();

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glGetDoublev(GL_MODELVIEW_MATRIX,temp_matrix);
	glTranslatef(-position.xyz[0],-position.xyz[1],-position.xyz[2]);
	glPushMatrix();
}

void Camera::MoveFw(float velocity)
{
	position.xyz[0]-=(float)(SIN(-yrot)*COS(xrot))*velocity;
	position.xyz[1]-=(float)(COS(-yrot)*COS(xrot))*velocity;
	position.xyz[2]-=(float)SIN(xrot)*velocity;
}

void Camera::MoveBw(float velocity)
{
	position.xyz[0]+=(float)(SIN(-yrot)*COS(xrot))*velocity;
	position.xyz[1]+=(float)(COS(-yrot)*COS(xrot))*velocity;
	position.xyz[2]+=(float)SIN(xrot)*velocity;
}

void Camera::MoveL(float velocity)
{
	position.xyz[0]-=(float)COS(yrot)*velocity;
	position.xyz[2]-=(float)SIN(yrot)*velocity;
}

void Camera::MoveR(float velocity)
{
	position.xyz[0]+=(float)COS(yrot)*velocity;
	position.xyz[2]+=(float)SIN(yrot)*velocity;
}

void Camera::MoveUp(float velocity)
{
	position.xyz[1]+=velocity;
}

void Camera::MoveDown(float velocity)
{
	position.xyz[1]-=velocity;
}

void Camera::RotateX(float rot)
{
	xrot+=rot;
	/*if(xrot>90.0f)
		xrot=90.0f;
	else if(xrot<-90.0f)
		xrot=-90.0f;*/
}

void Camera::RotateY(float rot)
{
	yrot+=rot;
}

void Camera::CalcViewFrustumPlanes()
{
	static float p_matrix[16],m_matrix[16],matrix[16];
	float length;

	glGetFloatv(GL_MODELVIEW_MATRIX,m_matrix);
	glGetFloatv(GL_PROJECTION_MATRIX,p_matrix);

	MatrixConcatenate(matrix,m_matrix,p_matrix);

	v_frustum[0].normal.xyz[0]=(matrix[3]+matrix[0]);
	v_frustum[0].normal.xyz[1]=(matrix[7]+matrix[4]);
	v_frustum[0].normal.xyz[2]=(matrix[11]+matrix[8]);
	v_frustum[0].distance=(matrix[15]+matrix[12]);

	v_frustum[1].normal.xyz[0]=(matrix[3]-matrix[0]);
	v_frustum[1].normal.xyz[1]=(matrix[7]-matrix[4]);
	v_frustum[1].normal.xyz[2]=(matrix[11]-matrix[8]);
	v_frustum[1].distance=(matrix[15]-matrix[12]);

	v_frustum[2].normal.xyz[0]=(matrix[3]-matrix[1]);
	v_frustum[2].normal.xyz[1]=(matrix[7]-matrix[5]);
	v_frustum[2].normal.xyz[2]=(matrix[11]-matrix[9]);
	v_frustum[2].distance=(matrix[15]-matrix[13]);

	v_frustum[3].normal.xyz[0]=(matrix[3]+matrix[1]);
	v_frustum[3].normal.xyz[1]=(matrix[7]+matrix[5]);
	v_frustum[3].normal.xyz[2]=(matrix[11]+matrix[9]);
	v_frustum[3].distance=(matrix[15]+matrix[13]);

	v_frustum[4].normal.xyz[0]=(matrix[3]+matrix[2]);
	v_frustum[4].normal.xyz[1]=(matrix[7]+matrix[6]);
	v_frustum[4].normal.xyz[2]=(matrix[11]+matrix[10]);
	v_frustum[4].distance=(matrix[15]+matrix[14]);

	v_frustum[5].normal.xyz[0]=(matrix[3]-matrix[2]);
	v_frustum[5].normal.xyz[1]=(matrix[7]-matrix[6]);
	v_frustum[5].normal.xyz[2]=(matrix[11]-matrix[10]);
	v_frustum[5].distance=(matrix[15]-matrix[14]);

	// vector normalizing
	for(int i=0;i<6;i++)
	{
		length=1.0f/v_frustum[i].normal.Length();
		v_frustum[i].normal.xyz[0]*=length;
		v_frustum[i].normal.xyz[1]*=length;
		v_frustum[i].normal.xyz[2]*=length;
		v_frustum[i].distance*=length;
	}
}
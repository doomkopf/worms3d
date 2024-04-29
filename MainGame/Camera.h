#ifndef CAMERA
#define CAMERA

#include "math.h"

class Camera
{
public:
	Camera()
	{
		xrot=0;
		yrot=0;
	}
	void Init(float,float,float);
	void Update(float,float,float,float,float,float);
	void Update();
	void MoveFw(float);
	void MoveBw(float);
	void MoveL(float);
	void MoveR(float);
	void MoveUp(float);
	void MoveDown(float);
	void RotateX(float);
	void RotateY(float);
	void CalcViewFrustumPlanes();

	float xrot,yrot;

	CVector3f position;
	double temp_matrix[16]; // for saving a matrix
	Plane v_frustum[6];
};

#endif
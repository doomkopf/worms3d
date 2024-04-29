#ifndef CVECTOR3F
#define CVECTOR3F

class CVector3f
{
public:
	CVector3f() {}
	CVector3f(float,float,float);

	void Set(float,float,float);
	void Inverse();

	CVector3f operator + (const CVector3f &) const;
	CVector3f operator -(const CVector3f &) const;
	CVector3f operator *(float) const;
	CVector3f operator /(float) const;
	void operator +=(const CVector3f &);
	void operator -=(const CVector3f &);
	void operator *=(float);
	void operator /=(float);

	/*float DotProduct(const CVector3f &) const;
	CVector3f CrossProduct(const CVector3f &) const;
	void Cross(const CVector3f &);*/
	float Length() const;
	void Normalize();

	float xyz[3];
};

class CVertex3f
{
public:
	CVector3f v;
	float tu,tv;
};

#endif
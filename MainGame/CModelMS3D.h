#ifndef CMODELMS3D
#define CMODELMS3D

typedef struct
{
	char id[10];
	int version;
} MS3D_HEADER;

typedef struct
{
	unsigned char flags;
	unsigned char refcount;
	char boneID;
	float vertex[3];
} MS3D_VERTEX;

typedef struct
{
	unsigned short flags;
	unsigned short vertex[3];
	float normal[3][3];
	float u[3];
	float v[3];
	unsigned char smoothing_group;
	unsigned char group;
} MS3D_TRIANGLE;

typedef struct
{
	unsigned char flags;
	char name[32];
	unsigned short num_triangles;
	unsigned short *triangle;
	char material;
} MS3D_GROUP;

class CModelMS3D
{
public:
	CModelMS3D();
	bool Load(char *);
	void SetTexture(unsigned int);
	void Draw();
	~CModelMS3D();

protected:
	MS3D_VERTEX *vertex;
	MS3D_TRIANGLE *triangle;
	MS3D_GROUP *group;
	unsigned short num_vertices;
	unsigned short num_triangles;
	unsigned short num_groups;
	unsigned int texture;
	bool loaded;
};

#endif
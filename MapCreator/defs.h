typedef struct
{
	float x,y,z;
} point3f;

typedef struct
{
	point3f normal;
	float distance;
} Plane;

typedef struct
{
	int vertex[3];
} Triangle;

typedef struct
{
	float u,v;
} Texcoord;
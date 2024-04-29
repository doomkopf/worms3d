#ifndef DEFS
#define DEFS

#define VERSION "Main Game"
#define OBJECT_RADIUS 20.0f
#define VERTEX_SPACE 64.0f
#define NUM_WEAPONS 5

typedef struct
{
	float x,y;
} point2f;

typedef struct
{
	int vertex[3];
} Triangle;

typedef struct
{
	float u,v;
} Texcoord;

#endif
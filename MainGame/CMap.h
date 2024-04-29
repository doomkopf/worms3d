#ifndef CMAP
#define CMAP

#include "defs.h"
#include "CPlayer.h"
#include "CParticleSource.h"

#define MAX_PARTICLE_SOURCES 16

typedef enum
{
	NO_SHADE,FLAT,GOURAUD
} t_shademode;

typedef struct
{
	unsigned char l[6];
	char count;
} temp_lights;

typedef struct
{
	float max_x,max_z,min_x,min_z;
	bool visible;
} t_sector;

typedef struct
{
	unsigned char r,g,b;
} t_diffuse;


class CMap
{
public:
	CMap();
	bool Load(char *);
	void DrawSky();
	void DrawLand();
	int CheckCollision(CObject *);
	bool GetCollisionPoint(CObject *,CVector3f *);
	bool GetCollisionPoint(CVector3f &,CVector3f &,CVector3f *);
	void ClipDisplacement(CObject *);
	void DeformGeometry(CVector3f,float);
	int StartNewParticleSource(float,float,float,float,bool);
	void StopParticleSource(int);
	void Update();
	void DrawStuff();
	void SetValidPlayerPositions();
	void Destruct();
	~CMap() { Destruct(); }

	bool loaded;
	t_shademode shademode;
	CVector3f box_min,box_max;
	unsigned char map_type;

protected:
	bool ReadColorMaps();
	void CalcPlanesAndShades();
	bool CheckIfValidPlayerPosition(CVector3f &,CVector3f &);
	void CalcAABB();
	void CreateSectors();
	void CullSectors(Camera *);
	int FindSector(CObject *);

	CVector3f *vertex;
	Triangle *tri;
	Texcoord *tc;
	Plane *plane;
	t_diffuse *shade_flat;
	t_diffuse *shade_gouraud;
	temp_lights *light_vertex;
	bool *hit;
	t_sector *sector;
	int *tri_sec;
	CVector3f *test;

	int num_vertices;
	int num_triangles;
	int num_sectors;

	int *collision;

	CParticleSource part_source[MAX_PARTICLE_SOURCES];

	unsigned int land_tex1,
		land_tex2,
		water_tex,
		sky_tex;

	t_diffuse grass_col[16],ice_col[8],rock_col[8],sand_col[8];
};

#endif
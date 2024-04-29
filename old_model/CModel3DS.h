#ifndef CMODEL3DS
#define CMODEL3DS

#include <stdio.h>
#include <windows.h>

typedef struct _map_list
{
	char filename[256];
	float u,v;
	float uoff,voff;
	float rot;
	_map_list *next;
} map_list;

typedef struct _mat_list
{
	char name[200];
	DWORD ambient;
	DWORD diffuse;
	DWORD specular;
	_map_list *htex, *ttex;
	_mat_list *next;
} mat_list;

typedef struct _face_mat
{
	char name[200];
	WORD ne;
	WORD *faces;
	_face_mat *next;
} face_mat;

typedef struct _mesh_object
{
	char name[200];
	float *vlst;
	WORD *flst;
	WORD nv;
	WORD nf;
	WORD mnv;
	float *mc;
	float lmat[4][4];
	_mesh_object *next;
	face_mat *fhead, *ftail;
} mesh_object;


class CModel3DS
{
public:
	CModel3DS();
	~CModel3DS();
	bool Load(char *);
	void Draw();

	bool loaded;

protected:
	void ReadObject();
	unsigned char ReadChar();
	unsigned int ReadInt();
	unsigned long ReadLong();
	void read_mat(DWORD);
	void read_mesh(DWORD);
	void read_object(DWORD);
	int read_3ds();
	int read_primary_chunk();

	FILE *file1;
	mesh_object *head,*tail;
	mat_list *mathead,*mattail;
	map_list *maphead,*maptail;
};

#endif
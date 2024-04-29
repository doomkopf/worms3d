#ifndef CMESHLOADER
#define CMESHLOADER

#include "CModelMD2.h"
#include "CModelMS3D.h"
#include "meshes.h"

class CMeshLoader
{
public:
	bool LoadMeshes();
	CModelMD2 *GetAnimModel(int);
	CModelMS3D *GetStaticModel(int);

protected:
	CModelMD2 model_md2[NUM_A_MODELS];
	CModelMS3D model_ms3d[NUM_S_MODELS];
	char name_md2[NUM_A_MODELS][32];
	char name_ms3d[NUM_S_MODELS][32];
};

#endif
#include "CMeshLoader.h"
#include "CMain.h"

extern CMain main_app;

bool CMeshLoader::LoadMeshes()
{
	strcpy(name_md2[A_MODEL_TEAM1],A_MODEL_TEAM1_NAME);
	strcpy(name_md2[A_MODEL_TEAM2],A_MODEL_TEAM2_NAME);
	model_md2[A_MODEL_TEAM1].SetTexture(main_app.GetTextureLoader()->GetTexture(TEX_TEAM1));
	model_md2[A_MODEL_TEAM2].SetTexture(main_app.GetTextureLoader()->GetTexture(TEX_TEAM2));

	strcpy(name_ms3d[S_MODEL_GRENADE],S_MODEL_GRENADE_NAME);
	model_ms3d[S_MODEL_GRENADE].SetTexture(main_app.GetTextureLoader()->GetTexture(TEX_GRENADE));

	for(int i=0;i<NUM_A_MODELS;i++)
	{
		if(!model_md2[i].Load(name_md2[i]))
			return false;
	}

	for(i=0;i<NUM_S_MODELS;i++)
	{
		if(!model_ms3d[i].Load(name_ms3d[i]))
			return false;
	}

	return true;
}

CModelMD2 *CMeshLoader::GetAnimModel(int index)
{
	return &model_md2[index];
}

CModelMS3D *CMeshLoader::GetStaticModel(int index)
{
	return &model_ms3d[index];
}
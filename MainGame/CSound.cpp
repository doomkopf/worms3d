#include "CSound.h"
#include "CMain.h"

extern CMain main_app;

CSound::CSound()
{
	loaded=false;
}

bool CSound::Init()
{
	/*CoInitialize(NULL);

	CoCreateInstance(CLSID_DirectMusicLoader,
		NULL,
		CLSCTX_INPROC,
		IID_IDirectMusicLoader8,
		(void **)&loader);

	for(int i=0;i<NUM_SOUNDS;i++)
	{
		CoCreateInstance(CLSID_DirectMusicPerformance,
			NULL,
			CLSCTX_INPROC,
			IID_IDirectMusicPerformance8,
			(void **)&performance[i]);

		performance[i]->InitAudio(NULL,
			NULL,
			main_app.GetMainWindow()->hwnd,
			DMUS_APATH_DYNAMIC_STEREO,
			64,
			DMUS_AUDIOF_ALL,
			NULL);
	}
	for(i=0;i<NUM_SOUNDS;i++)
	{
		CoCreateInstance(CLSID_DirectMusicSegment,
			NULL,CLSCTX_INPROC,
			IID_IDirectMusicSegment8,
			(void **)&segment[i]);
	}

	if(!LoadSounds())
		return false;

	loaded=true;*/
	return true;
}

bool CSound::LoadSounds()
{
	/*WCHAR w_file[80];
	char sound[NUM_SOUNDS][80];

	strcpy(sound[SND_SHOTGUN],"sounds/awp1.wav");
	strcpy(sound[SND_GRENADE_SHOT],"sounds/grenade_shot.wav");
	strcpy(sound[SND_ROCKET_SHOT],"sounds/rocket_shot.wav");
	strcpy(sound[SND_GRENADE_EXPLOSION],"sounds/explode4.wav");
	strcpy(sound[SND_JETPACK],"sounds/jetpack.wav");
	strcpy(sound[SND_MINIGUN],"sounds/minigun_shot.wav");

	for(int i=0;i<NUM_SOUNDS;i++)
	{
		MultiByteToWideChar(CP_ACP,0,sound[i],-1,w_file,80);
		loader->LoadObjectFromFile(CLSID_DirectMusicSegment,
			IID_IDirectMusicSegment8,
			w_file,
			(void **)&segment[i]);
		segment[i]->Download(performance[i]);
	}*/

	return true;
}

void CSound::Play(int index,int repeats)
{
	/*if(repeats==SND_INFINITE)
		segment[index]->SetRepeats(DMUS_SEG_REPEAT_INFINITE);
	else
		segment[index]->SetRepeats(repeats);
	performance[index]->PlaySegmentEx(segment[index],NULL,NULL,0,0,NULL,NULL,NULL);*/
}

void CSound::Stop(int index)
{
	//performance[index]->StopEx(segment[index],NULL,NULL);
}

CSound::~CSound()
{
	/*if(loaded)
	{
		for(int i=0;i<NUM_SOUNDS;i++)
			segment[i]->Release();
		for(i=0;i<NUM_SOUNDS;i++)
		{
			performance[i]->CloseDown();
			performance[i]->Release();
		}
		loader->Release();
		CoUninitialize();
	}*/
}
#ifndef CSOUND
#define CSOUND

//#include <dmusici.h>
//#include <dsound.h>
#include "sounds.h"

//#pragma comment (lib,"dxguid.lib")
//#pragma comment (lib,"dsound.lib")

#define SND_INFINITE -1

class CSound
{
public:
	CSound();
	~CSound();
	bool Init();
	bool LoadSounds();
	void Play(int,int repeats=0);
	void Stop(int);

protected:
	bool loaded;
	//IDirectMusicLoader8 *loader;
	//IDirectMusicPerformance8 *performance[NUM_SOUNDS];
	//IDirectMusicSegment8 *segment[NUM_SOUNDS];
};

#endif
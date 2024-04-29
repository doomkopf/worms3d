#ifndef CMODELMD2
#define CMODELMD2

#include <stdio.h>
#include "defs.h"

#define IDLE1				0
#define RUN					1
#define SHOT_STAND			2
#define SHOT_SHOULDER		3
#define JUMP				4
#define IDLE2				5
#define SHOT_FALLDOWN		6
#define IDLE3				7
#define IDLE4				8
#define CROUCH				9
#define CROUCH_CRAWL		10
#define CROUCH_IDLE			11
#define CROUCH_DEATH		12
#define DEATH_FALLBACK		13
#define DEATH_FALLFORWARD	14
#define DEATH_FALLBACKSLOW	15

#define IDLE1_START					0
#define IDLE1_END					39
#define RUN_START					40
#define RUN_END						45
#define SHOT_STAND_START			46
#define SHOT_STAND_END				60
#define SHOT_SHOULDER_START			61
#define SHOT_SHOULDER_END			66
#define JUMP_START					67
#define JUMP_END					73
#define IDLE2_START					74
#define IDLE2_END					95
#define SHOT_FALLDOWN_START			96
#define SHOT_FALLDOWN_END			112
#define IDLE3_START					113
#define IDLE3_END					122
#define IDLE4_START					123
#define IDLE4_END					135
#define CROUCH_START				136
#define CROUCH_END					154
#define CROUCH_CRAWL_START			155
#define CROUCH_CRAWL_END			161
#define CROUCH_IDLE_START			162
#define CROUCH_IDLE_END				169
#define CROUCH_DEATH_START			170
#define CROUCH_DEATH_END			177
#define DEATH_FALLBACK_START		178
#define DEATH_FALLBACK_END			185
#define DEATH_FALLFORWARD_START		186
#define DEATH_FALLFORWARD_END		190
#define DEATH_FALLBACKSLOW_START	191
#define DEATH_FALLBACKSLOW_END		198

typedef struct
{
	int magic;
	int version;
	int skinWidth;
	int skinHeight;
	int frameSize;
	int numSkins;
	int numVertices;
	int numTexcoords;
	int numTriangles;
	int numGlCommands;
	int numFrames;
	int offsetSkins;
	int offsetTexcoords;
	int offsetTriangles;
	int offsetFrames;
	int offsetGlCommands;
	int offsetEnd;
} MD2_HEADER;

typedef struct
{
	unsigned char vertex[3];
	unsigned char lightNormalIndex;
} MD2_VERTEX;

typedef struct
{
	float scale[3];
	float translate[3];
	char name[16];
	MD2_VERTEX vertices[1];
} MD2_FRAME;

typedef struct
{
	float x,y,z;
	float u,v;
} MD2_MODELVERTEX;

class CModelMD2
{
public:
	CModelMD2();
	~CModelMD2();
	bool Load(char *);
	void Render(int);
	void Animate(float);
	void SetState(int);

	bool loaded;

protected:
	char *frames;
	long *glCommands;
	int numFrames;
	int numGlCommands;
	int frameSize;
	int numTriangles;
	int currentFrame;
	int nextFrame;
	int endFrame;
	int stateStart;
	int stateEnd;
	float interpolation;
	unsigned int skin;
};

#endif
#include "CModelMD2.h"
#include "texload.h"
#include <windows.h>
#include <gl/gl.h>

CModelMD2::CModelMD2()
{
	frames=NULL;
	glCommands=NULL;
	numFrames=0;
	numGlCommands=0;
	frameSize=0;
	currentFrame=IDLE1_START;
	nextFrame=currentFrame+1;
	endFrame=IDLE1_END;
	stateStart=IDLE1_START;
	stateEnd=IDLE1_END;
	interpolation=0.0f;
	loaded=false;
}

bool CModelMD2::Load(char *name)
{
	MD2_HEADER header;
	char filename[80];
	strcpy(filename,name);
	strcat(filename,".md2");
	FILE *file1=fopen(filename,"rb");
	if(!file1)
		return false;

	fread(&header,sizeof(header),1,file1);

	frames = new char[header.frameSize*header.numFrames];
	fseek(file1,header.offsetFrames,SEEK_SET);
	fread(frames,header.frameSize*header.numFrames,1,file1);

	glCommands = new long[header.numGlCommands*sizeof(long)];
	fseek(file1,header.offsetGlCommands,SEEK_SET);
	fread(glCommands,header.numGlCommands*sizeof(long),1,file1);

	numFrames=header.numFrames;
	numGlCommands=header.numGlCommands;
	frameSize=header.frameSize;
	numTriangles=header.numTriangles;

	fclose(file1);

	strcpy(filename,name);
	strcat(filename,".tga");
	if(!LoadTextureTGA(filename,&skin))
		return false;

	loaded=true;

	return true;
}

void CModelMD2::Render(int numFrame)
{
	static MD2_MODELVERTEX vertList[100];

	MD2_FRAME *currentFrame;
	float v1[3];
	long *command;
	float texcoord[2];
	int loop;
	int vertIndex;
	int type;
	int numVertex;
	int index;

	currentFrame=(MD2_FRAME*)((char*)frames+frameSize*numFrame);
	command=glCommands;

	//glRotatef(90.0f,0,1,0);
	//glRotatef(rotation_y,0,-1,0);

	glCullFace(GL_FRONT);

	glBindTexture(GL_TEXTURE_2D,skin);

	while((*command)!=0)
	{
		if(*command>0)
		{
			numVertex=*command;
			type=0;
		}
		else
		{
			numVertex=*command;
			type=1;
		}
		command++;

		if(numVertex<0)
			numVertex=-numVertex;

		index=0;
		for(loop=0;loop<numVertex;loop++)
		{
			vertList[index].u=*((float*)command);
			command++;
			vertList[index].v=*((float*)command);
			command++;
			vertIndex=*command;
			command++;

			vertList[index].x=((currentFrame->vertices[vertIndex].vertex[0]* 
								  currentFrame->scale[0])+ 
								  currentFrame->translate[0]);
			vertList[index].z=-((currentFrame->vertices[vertIndex].vertex[1]* 
								  currentFrame->scale[1])+ 
								  currentFrame->translate[1]);
			vertList[index].y=((currentFrame->vertices[vertIndex].vertex[2]* 
								  currentFrame->scale[2])+ 
								  currentFrame->translate[2]);
			index++;
		}
		if(type==0)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for(loop=0;loop<index;loop++)
			{
				v1[0]=(vertList[loop].x);
				v1[1]=(vertList[loop].y);
				v1[2]=(vertList[loop].z);

				texcoord[0]= vertList[loop].u;
				texcoord[1]= vertList[loop].v;

				glTexCoord2fv(texcoord);
				glVertex3fv(v1);
			}
			glEnd();
		}
		else
		{
			glBegin(GL_TRIANGLE_FAN);
			for(loop=0;loop<index;loop++)
			{
				v1[0]=(vertList[loop].x);
				v1[1]=(vertList[loop].y);
				v1[2]=(vertList[loop].z);

				texcoord[0]= vertList[loop].u;
				texcoord[1]= vertList[loop].v;

				glTexCoord2fv(texcoord);
				glVertex3fv(v1);
			}
			glEnd();
		}
	}
	glCullFace(GL_BACK);
}

void CModelMD2::Animate(float percent)
{
	if(!loaded)
		return;

	if(currentFrame==-1 || currentFrame>stateEnd)
	{
		currentFrame=stateStart;
		nextFrame=currentFrame+1;
		endFrame=stateEnd;
	}
	if(interpolation>1.0f)
	{
		interpolation=0.0f;
		currentFrame=nextFrame;
		nextFrame=currentFrame+1;
	}
	interpolation+=percent;
	Render(currentFrame);
}

void CModelMD2::SetState(int state)
{
	switch(state)
	{
		case IDLE1:
			stateStart	 = IDLE1_START;
			stateEnd	 = IDLE1_END;
			currentFrame =-1;
			break;
		case RUN:
			stateStart	 = RUN_START;
			stateEnd	 = RUN_END;
			currentFrame =-1;
			break;
		case SHOT_STAND:
			stateStart	 = SHOT_STAND_START;
			stateEnd	 = SHOT_STAND_END;
			currentFrame =-1;
			break;
		case SHOT_SHOULDER:
			stateStart	 = SHOT_SHOULDER_START;
			stateEnd	 = SHOT_SHOULDER_END;
			currentFrame =-1;
			break;
		case JUMP:
			stateStart	 = JUMP_START;
			stateEnd	 = JUMP_END;
			currentFrame =-1;
			break;
		case IDLE2:
			stateStart	 = IDLE2_START;
			stateEnd	 = IDLE2_END;
			currentFrame =-1;
			break;
		case SHOT_FALLDOWN:
			stateStart	 = SHOT_FALLDOWN_START;
			stateEnd	 = SHOT_FALLDOWN_END;
			currentFrame =-1;
			break;
		case IDLE3:
			stateStart	 = IDLE3_START;
			stateEnd	 = IDLE3_END;
			currentFrame =-1;
			break;
		case IDLE4:
			stateStart	 = IDLE4_START;
			stateEnd	 = IDLE4_END;
			currentFrame =-1;
			break;
		case CROUCH:
			stateStart	 = CROUCH_START;
			stateEnd	 = CROUCH_END;
			currentFrame =-1;
			break;
		case CROUCH_CRAWL:
			stateStart	 = CROUCH_CRAWL_START;
			stateEnd	 = CROUCH_CRAWL_END;
			currentFrame =-1;
			break;
		case CROUCH_IDLE:
			stateStart	 = CROUCH_IDLE_START;
			stateEnd	 = CROUCH_IDLE_END;
			currentFrame =-1;
			break;
		case CROUCH_DEATH:
			stateStart	 = CROUCH_DEATH_START;
			stateEnd	 = CROUCH_DEATH_END;
			currentFrame =-1;
			break;
		case DEATH_FALLBACK:
			stateStart	 = DEATH_FALLBACK_START;
			stateEnd	 = DEATH_FALLBACK_END;
			currentFrame =-1;
			break;
		case DEATH_FALLFORWARD:
			stateStart	 = DEATH_FALLFORWARD_START;
			stateEnd	 = DEATH_FALLFORWARD_END;
			currentFrame =-1;
			break;
		case DEATH_FALLBACKSLOW:
			stateStart	 = DEATH_FALLBACKSLOW_START;
			stateEnd	 = DEATH_FALLBACKSLOW_END;
			currentFrame =-1;
			break;
	}
}

CModelMD2::~CModelMD2()
{
	if(loaded)
	{
		delete frames;
		delete glCommands;

		loaded=false;
	}
}
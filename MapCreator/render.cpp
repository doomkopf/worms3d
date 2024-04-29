#include "render.h"
#include "GLWindow.h"
#include "CControl.h"
#include "Text.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "Math.h"
#include "texload.h"
#include <time.h>
#include <stdio.h>
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")

#ifdef MAP_SIZE
#undef MAP_SIZE
#endif
#ifdef VERTEX_SPACE
#undef VERTEX_SPACE
#endif
#define MAP_SIZE 128
#define VERTEX_SPACE 64.0f
#define NUM_TRIANGLES ( (MAP_SIZE-1)*(MAP_SIZE-1)*2 )
#define INC_RADIUS 400.0f
#define INC_SPEED 16 // higher -> slower

#define MAP_GRASS 0
#define MAP_ICE 1
#define MAP_ROCK 2
#define MAP_SAND 3
#define NUM_TYPES 4

extern GLWindow win;
extern float frametime;

CControl control;
Text text;

float rot_y,rot_x;
float trans_z;
int mx,my;
unsigned int test_tex;
unsigned char map_type=0;
bool text_input=false;

point3f vertex[MAP_SIZE][MAP_SIZE];
point3f normal[NUM_TRIANGLES];

void CalcNormals()
{
	int x,z,n=0;
	point3f tri[3];
	for(x=0;x<MAP_SIZE-1;x++)
	{
		for(z=0;z<MAP_SIZE-1;z++)
		{
			tri[0]=vertex[x][z];
			tri[1]=vertex[x][z+1];
			tri[2]=vertex[x+1][z];
			normal[n++]=CalcNormal(tri,3);
			tri[0]=vertex[x+1][z];
			tri[1]=vertex[x][z+1];
			tri[2]=vertex[x+1][z+1];
			normal[n++]=CalcNormal(tri,3);
		}
	}
}
/*
void CreateRandomMap()
{
	int x,z;

	srand((unsigned)time(NULL));

	for(x=0;x<MAP_SIZE;x++)
	{
		for(z=0;z<MAP_SIZE;z++)
		{
			vertex[x][z].x=VERTEX_SPACE*(float)x;
			vertex[x][z].y=float(rand()%20);
			vertex[x][z].z=VERTEX_SPACE*(float)z;
		}
	}

	CalcNormals();
}
*/
void CreateFlatMap()
{
	int x,z;

	for(x=0;x<MAP_SIZE;x++)
	{
		for(z=0;z<MAP_SIZE;z++)
		{
			vertex[x][z].x=(VERTEX_SPACE*(float)x)-(MAP_SIZE*VERTEX_SPACE)/2;
			vertex[x][z].y=0;
			vertex[x][z].z=(VERTEX_SPACE*(float)z)-(MAP_SIZE*VERTEX_SPACE)/2;
		}
	}

	CalcNormals();
}

void InitGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,400.0f/300.0f,1.0f,100000.0f);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPointSize(2.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

bool Init()
{
	InitGL();
	control.Init();
	text.Init(win.hdc,win.width,win.height);
	//CreateRandomMap();
	CreateFlatMap();
	LoadTextureTGA("test1.tga",&test_tex);

	rot_y=0;
	rot_x=45;
	trans_z=-6000;
	mx=win.width/2;
	my=win.height/2;

	return true;
}

void DrawCursor()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,win.width,win.height,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(mx,my,0);

	glColor3ub(255,255,255);
	glBegin(GL_TRIANGLES);
	glVertex2i(0,0);
	glVertex2i(0,10);
	glVertex2i(10,10);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void Point2DTo3D(int x,int y,point3f *p,bool far_c)
{
	static double modelview[16],projection[16];
	int viewport[4];
	double temp_x,temp_y,temp_z;

	glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
	glGetDoublev(GL_PROJECTION_MATRIX,projection);
	glGetIntegerv(GL_VIEWPORT,viewport);

	if(!far_c)
	{
		gluUnProject((double)x,double(viewport[3]-y),0,modelview,projection,viewport,
			&temp_x,&temp_y,&temp_z);
	}
	else
	{
		gluUnProject((double)x,double(viewport[3]-y),1,modelview,projection,viewport,
			&temp_x,&temp_y,&temp_z);
	}
	p->x=(float)temp_x;
	p->y=(float)temp_y;
	p->z=(float)temp_z;
}

void ShiftVerticesInRadius(bool inc)
{
	point3f p_near,p_far,v,point;
	Plane p;
	float dist;

	p.normal.x=0;
	p.normal.y=1;
	p.normal.z=0;
	p.distance=0;

	Point2DTo3D(mx,my,&p_near,false);
	Point2DTo3D(mx,my,&p_far,true);

	v=VectorSubtract(p_far,p_near);
	VectorNormalize(&v);

	if(!GetIntersectionPoint_ray_plane(p_near,v,p,&point))
		return;

	for(int x=0;x<MAP_SIZE;x++)
	{
		for(int z=0;z<MAP_SIZE;z++)
		{
			v.x=vertex[x][z].x;
			v.y=0;
			v.z=vertex[x][z].z;
			dist=GetDistance_pp(point,v);
			if( dist<INC_RADIUS && x!=0 && z!=0 && x!=MAP_SIZE-1 && z!=MAP_SIZE-1 )
			{
				if(inc)
					vertex[x][z].y+=(((INC_RADIUS)-dist)/INC_SPEED)*frametime*0.05f;
				else
				{
					vertex[x][z].y-=(((INC_RADIUS)-dist)/INC_SPEED)*frametime*0.05f;
					if(vertex[x][z].y<0)
						vertex[x][z].y=0;
				}
			}
		}
	}

	CalcNormals();
}

void SaveMap(bool raw)
{
	int x,z,num_tri=0,i=0;
	static point3f p[MAP_SIZE*MAP_SIZE];
	static Texcoord t[MAP_SIZE*MAP_SIZE];
	static Triangle tri[NUM_TRIANGLES];
	static bool added[MAP_SIZE][MAP_SIZE];
	static int test[MAP_SIZE][MAP_SIZE];
	FILE *file1;

	if(raw)
	{
		file1=fopen("test.map","w+b");

		for(x=0;x<MAP_SIZE;x++)
		{
			for(z=0;z<MAP_SIZE;z++)
				fwrite(&vertex[x][z].y,sizeof(float),1,file1);
		}

		fclose(file1);
	}
	else
	{
		for(x=0;x<MAP_SIZE;x++)
		{
			for(z=0;z<MAP_SIZE;z++)
				added[x][z]=false;
		}

		file1=fopen("test.tri","w+b");

		for(x=0;x<MAP_SIZE-1;x++)
		{
			for(z=0;z<MAP_SIZE-1;z++)
			{
				if(vertex[x][z].y>0 || vertex[x][z+1].y>0 || vertex[x+1][z].y>0)
				{
					if(!added[x][z])
					{
						p[i]=vertex[x][z];
						t[i].u=(float)x;
						t[i].v=(float)z;
						added[x][z]=true;
						test[x][z]=i++;
					}
					tri[num_tri].vertex[0]=test[x][z];
					if(!added[x][z+1])
					{
						p[i]=vertex[x][z+1];
						t[i].u=(float)x;
						t[i].v=(float)z+1;
						added[x][z+1]=true;
						test[x][z+1]=i++;
					}
					tri[num_tri].vertex[1]=test[x][z+1];
					if(!added[x+1][z])
					{
						p[i]=vertex[x+1][z];
						t[i].u=(float)x+1;
						t[i].v=(float)z;
						added[x+1][z]=true;
						test[x+1][z]=i++;
					}
					tri[num_tri].vertex[2]=test[x+1][z];
					num_tri++;
				}

				if(vertex[x+1][z].y>0 || vertex[x][z+1].y>0 || vertex[x+1][z+1].y>0)
				{
					if(!added[x+1][z])
					{
						p[i]=vertex[x+1][z];
						t[i].u=(float)x+1;
						t[i].v=(float)z;
						added[x+1][z]=true;
						test[x+1][z]=i++;
					}
					tri[num_tri].vertex[0]=test[x+1][z];
					if(!added[x][z+1])
					{
						p[i]=vertex[x][z+1];
						t[i].u=(float)x;
						t[i].v=(float)z+1;
						added[x][z+1]=true;
						test[x][z+1]=i++;
					}
					tri[num_tri].vertex[1]=test[x][z+1];
					if(!added[x+1][z+1])
					{
						p[i]=vertex[x+1][z+1];
						t[i].u=(float)x+1;
						t[i].v=(float)z+1;
						added[x+1][z+1]=true;
						test[x+1][z+1]=i++;
					}
					tri[num_tri].vertex[2]=test[x+1][z+1];
					num_tri++;
				}
			}
		}

		// map type
		fwrite(&map_type,sizeof(unsigned char),1,file1);
		// number of vertices
		fwrite(&i,sizeof(int),1,file1);
		// number of triangles
		fwrite(&num_tri,sizeof(int),1,file1);
		// vertices
		fwrite(&p,sizeof(point3f),i,file1);
		// texture coords (same number as vertices)
		fwrite(&t,sizeof(Texcoord),i,file1);
		// triangles (three integers indicating points in the vertex array)
		fwrite(&tri,sizeof(Triangle),num_tri,file1);

		fclose(file1);
	}
}

void LoadMap()
{
	FILE *file1;

	file1=fopen("test.map","rb");
	if(!file1)
		return;

	for(int x=0;x<MAP_SIZE;x++)
	{
		for(int z=0;z<MAP_SIZE;z++)
		{
			fread(&vertex[x][z].y,sizeof(float),1,file1);
		}
	}

	fclose(file1);

	CalcNormals();
}

void GetInput()
{
	control.Update();

	if(control.key_d[KEY_ESCAPE])
		win.quit=true;

	if(text_input)
	{
	}
	else
	{
		if(control.key_d[KEY_BUP])
			trans_z+=1.0f*frametime;
		if(control.key_d[KEY_BDOWN])
			trans_z-=1.0f*frametime;
		if(control.key_d[KEY_LEFT])
			rot_y-=0.1f*frametime;
		if(control.key_d[KEY_RIGHT])
			rot_y+=0.1f*frametime;
		if(control.key_d[KEY_UP])
		rot_x-=0.1f*frametime;
		if(control.key_d[KEY_DOWN])
			rot_x+=0.1f*frametime;
		if(control.hit_d[KEY_F1])
			LoadMap();
		if(control.hit_d[KEY_F2])
			SaveMap(true);
		if(control.hit_d[KEY_F3])
			SaveMap(false);
		if(control.hit_d[KEY_T])
		{
			map_type++;
			if(map_type>=NUM_TYPES)
				map_type=0;
		}

		mx+=int(control.mouse_x*3);
		my+=int(control.mouse_y*3);

		if(control.key_d[KEY_MWUP])
			trans_z+=10*frametime;
		if(control.key_d[KEY_MWDOWN])
			trans_z-=10*frametime;

		if(control.key_d[KEY_MMIDDLE])
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

		if(control.key_d[KEY_MLEFT])
			ShiftVerticesInRadius(true);

		if(control.key_d[KEY_MRIGHT])
			ShiftVerticesInRadius(false);
	}
}

void Render()
{
	GetInput();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0,0,trans_z);
	glRotatef(rot_x,1,0,0);
	glRotatef(rot_y,0,1,0);

	int n=0;
	glBindTexture(GL_TEXTURE_2D,test_tex);
	glBegin(GL_TRIANGLES);
	for(int x=0;x<MAP_SIZE-1;x++)
	{
		for(int z=0;z<MAP_SIZE-1;z++)
		{
			glNormal3f(normal[n].x,normal[n].y,normal[n++].z);
			glTexCoord2f((float)x,(float)z);
			glVertex3f(vertex[x][z].x,vertex[x][z].y,vertex[x][z].z);
			glTexCoord2f((float)x,(float)z+1);
			glVertex3f(vertex[x][z+1].x,vertex[x][z+1].y,vertex[x][z+1].z);
			glTexCoord2f((float)x+1,(float)z);
			glVertex3f(vertex[x+1][z].x,vertex[x+1][z].y,vertex[x+1][z].z);
			glNormal3f(normal[n].x,normal[n].y,normal[n++].z);
			glTexCoord2f((float)x+1,(float)z);
			glVertex3f(vertex[x+1][z].x,vertex[x+1][z].y,vertex[x+1][z].z);
			glTexCoord2f((float)x,(float)z+1);
			glVertex3f(vertex[x][z+1].x,vertex[x][z+1].y,vertex[x][z+1].z);
			glTexCoord2f((float)x+1,(float)z+1);
			glVertex3f(vertex[x+1][z+1].x,vertex[x+1][z+1].y,vertex[x+1][z+1].z);
		}
	}
	glEnd();

	DrawCursor();


	glDisable(GL_LIGHTING);

	text.Print(0,0,"F1: Load  F2: Save  F3: Compile");
	switch(map_type)
	{
	case MAP_GRASS:
		text.Print(0,20,"Map-Type: Grass");
		break;

	case MAP_ICE:
		text.Print(0,20,"Map-Type: Ice");
		break;

	case MAP_ROCK:
		text.Print(0,20,"Map-Type: Rock");
		break;

	case MAP_SAND:
		text.Print(0,20,"Map-Type: Sand");
		break;
	}

	glEnable(GL_LIGHTING);

	SwapBuffers(win.hdc);
}

void Destruct()
{
}
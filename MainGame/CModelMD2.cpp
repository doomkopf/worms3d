#include "CModelMD2.h"
#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include "texload.h"

CModelMD2::CModelMD2()
{
	loaded=false;
}

bool CModelMD2::Load(char *name)
{
	FILE *file1;
	char g_skins[MAX_MD2SKINS][64];
	dstvert_t base_st[MAX_VERTS];
	unsigned char buffer[MAX_VERTS*4+128];
	MD2HEADER modelheader;
	dtriangle_t tri;
	daliasframe_t *out;
	char temp[64];

	/*strcpy(temp,name);
	strcat(temp,".tga");
	if(!LoadTextureTGA(temp,&texture))
		return false;*/

	strcpy(temp,name);
	strcat(temp,".md2");
	file1=fopen(temp,"rb");
	if(!file1)
		return false;

	fread(&modelheader,sizeof(MD2HEADER),1,file1);

	num_frames=modelheader.num_frames;
	num_vertices=modelheader.num_xyz;
	num_triangles=modelheader.num_tris;
	index_list = new t_index_list[num_triangles];
	frame_list = new t_frame_list[num_frames];

	for(int i=0;i<num_frames;i++)
		frame_list[i].vertex = new t_vertex_list[num_vertices];

	fread(g_skins,1,modelheader.num_skins*MAX_SKINNAME,file1);
	fread(base_st,1,modelheader.num_st*sizeof(base_st[0]),file1);

	for(i=0;i<num_triangles;i++)
	{
		fread(&tri,sizeof(dtriangle_t),1,file1);
		index_list[i].a=tri.index_xyz[2];
		index_list[i].b=tri.index_xyz[1];
		index_list[i].c=tri.index_xyz[0];

		index_list[i].as=base_st[tri.index_st[2]].s;
		index_list[i].at=base_st[tri.index_st[2]].t;
		index_list[i].bs=base_st[tri.index_st[1]].s;
		index_list[i].bt=base_st[tri.index_st[1]].t;
		index_list[i].cs=base_st[tri.index_st[0]].s;
		index_list[i].ct=base_st[tri.index_st[0]].t;
	}

	for(i=0;i<num_triangles;i++)
	{
		index_list[i].as/=modelheader.skinwidth;
		index_list[i].bs/=modelheader.skinwidth;
		index_list[i].cs/=modelheader.skinwidth;
		index_list[i].at/=modelheader.skinheight;
		index_list[i].bt/=modelheader.skinheight;
		index_list[i].ct/=modelheader.skinheight;
	}

	for(i=0;i<num_frames;i++)
	{
		out=(daliasframe_t *)buffer;
		fread(out,1,modelheader.framesize,file1);
		for(int j=0;j<num_vertices;j++)
		{
			frame_list[i].vertex[j].x=out->verts[j].v[0] * out->scale[0] + out->translate[0];
			frame_list[i].vertex[j].y=out->verts[j].v[1] * out->scale[1] + out->translate[1];
			frame_list[i].vertex[j].z=out->verts[j].v[2] * out->scale[2] + out->translate[2];
		}
	}

	fclose(file1);

	loaded=true;

	return true;
}

void CModelMD2::SetTexture(unsigned int tex)
{
	texture=tex;
}

void CModelMD2::Render(int frame)
{
	if(!loaded)
		return;

	//static int frame=40,t=0;

	glBindTexture(GL_TEXTURE_2D,texture);

	glBegin(GL_TRIANGLES);
	for(int i=0;i<num_triangles;i++)
	{
		glTexCoord2f(index_list[i].as,-index_list[i].at);
		glVertex3f(frame_list[frame].vertex[index_list[i].a].x,
			frame_list[frame].vertex[index_list[i].a].y,
			frame_list[frame].vertex[index_list[i].a].z);
		glTexCoord2f(index_list[i].bs,-index_list[i].bt);
		glVertex3f(frame_list[frame].vertex[index_list[i].b].x,
			frame_list[frame].vertex[index_list[i].b].y,
			frame_list[frame].vertex[index_list[i].b].z);
		glTexCoord2f(index_list[i].cs,-index_list[i].ct);
		glVertex3f(frame_list[frame].vertex[index_list[i].c].x,
			frame_list[frame].vertex[index_list[i].c].y,
			frame_list[frame].vertex[index_list[i].c].z);
	}
	glEnd();

	/*t++;
	if(t>100)
	{
		frame++;
		t=0;
	}
	if(frame>45)
		frame=40;*/
}

void CModelMD2::Destruct()
{
	if(loaded)
	{
		delete [] index_list;
		for(int i=0;i<num_frames;i++)
			delete [] frame_list[i].vertex;
		delete [] frame_list;

		loaded=false;
	}
}

CModelMD2::~CModelMD2()
{
	Destruct();
}
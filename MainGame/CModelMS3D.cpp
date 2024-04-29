#include "CModelMS3D.h"
#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>

CModelMS3D::CModelMS3D()
{
	loaded=false;
}

bool CModelMS3D::Load(char *name)
{
	MS3D_HEADER header;

		char temp[64];

	strcpy(temp,name);
	strcat(temp,".ms3d");
	FILE *file1=fopen(temp,"rb");
	if(!file1)
		return false;

	fread(&header.id,sizeof(char),10,file1);
	fread(&header.version,sizeof(int),1,file1);
	if(strncmp(header.id,"MS3D000000",10)!=0)
		return false;
	if(header.version!=4)
		return false;

	fread(&num_vertices,sizeof(unsigned short),1,file1);
	vertex = new MS3D_VERTEX[num_vertices];
	//fread(vertex,sizeof(MS3D_VERTEX),num_vertices,file1);
	for(int i=0;i<num_vertices;i++)
	{
		fread(&vertex[i].flags,sizeof(unsigned char),1,file1);
		fread(vertex[i].vertex,sizeof(float),3,file1);
		fread(&vertex[i].boneID,sizeof(char),1,file1);
		fread(&vertex[i].refcount,sizeof(unsigned char),1,file1);
	}

	fread(&num_triangles,sizeof(unsigned short),1,file1);
	triangle = new MS3D_TRIANGLE[num_triangles];
	//fread(triangle,sizeof(MS3D_TRIANGLE),num_triangles,file1);
	for(i=0;i<num_triangles;i++)
	{
		fread(&triangle[i].flags,sizeof(unsigned short),1,file1);
		fread(triangle[i].vertex,sizeof(unsigned short),3,file1);
		fread(triangle[i].normal[0],sizeof(float),3,file1);
		fread(triangle[i].normal[1],sizeof(float),3,file1);
		fread(triangle[i].normal[2],sizeof(float),3,file1);
		fread(triangle[i].u,sizeof(float),3,file1);
		fread(triangle[i].v,sizeof(float),3,file1);
		fread(&triangle[i].smoothing_group,sizeof(unsigned char),1,file1);
		fread(&triangle[i].group,sizeof(unsigned char),1,file1);
	}

	fread(&num_groups,sizeof(unsigned short),1,file1);
	group = new MS3D_GROUP[num_groups];
	for(i=0;i<num_groups;i++)
	{
		fread(&group[i].flags,sizeof(unsigned char),1,file1);
		fread(group[i].name,sizeof(char),32,file1);
		fread(&group[i].num_triangles,sizeof(unsigned short),1,file1);
		group[i].triangle = new unsigned short[group[i].num_triangles];
		fread(group[i].triangle,sizeof(unsigned short),group[i].num_triangles,file1);
		fread(&group[i].material,sizeof(char),1,file1);
	}

	fclose(file1);

	loaded=true;

	return true;
}

void CModelMS3D::SetTexture(unsigned int tex)
{
	texture=tex;
}

void CModelMS3D::Draw()
{
	glColor3ub(255,255,255);
	glBindTexture(GL_TEXTURE_2D,texture);

	for(int i=0;i<num_groups;i++)
	{
		glBegin(GL_TRIANGLES);
		for(int j=0;j<group[i].num_triangles;j++)
		{
			int index=group[i].triangle[j];
			for(int k=0;k<3;k++)
			{
				//glNormal3fv(triangle[index].normal[k]);
				glTexCoord2f(triangle[index].u[k],-triangle[index].v[k]);
				glVertex3fv(vertex[triangle[index].vertex[k]].vertex);
			}
		}
		glEnd();
	}
}

CModelMS3D::~CModelMS3D()
{
	if(loaded)
	{
		delete [] vertex;
		delete [] triangle;
		for(int i=0;i<num_groups;i++)
			delete [] group[i].triangle;
		delete [] group;

		loaded=false;
	}
}
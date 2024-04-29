#include "CMap.h"
#include "texload.h"
#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include <time.h>
#include "math.h"
#include "CMain.h"

extern CMain main_app;

#define MAP_GRASS 0
#define MAP_ICE 1
#define MAP_ROCK 2
#define MAP_SAND 3

CMap::CMap()
{
	vertex=NULL;
	tri=NULL;
	tc=NULL;
	plane=NULL;
	shade_flat=NULL;
	shade_gouraud=NULL;
	light_vertex=NULL;
	hit=NULL;
	sector=NULL;
	tri_sec=NULL;
	collision=NULL;
	test=NULL;

	loaded=false;
	srand((unsigned)time(NULL));
	shademode=GOURAUD;
}

bool CMap::Load(char *name)
{
	FILE *file1=fopen(name,"rb");
	if(!file1 || loaded)
		return false;

	fread(&map_type,sizeof(unsigned char),1,file1);

	//map_type=MAP_ICE;

	switch(map_type)
	{
	case MAP_GRASS:
		land_tex1=main_app.GetTextureLoader()->GetTexture(TEX_GRASS1);
		land_tex2=main_app.GetTextureLoader()->GetTexture(TEX_GRASS2);
		water_tex=main_app.GetTextureLoader()->GetTexture(TEX_WATER1);
		sky_tex=main_app.GetTextureLoader()->GetTexture(TEX_SKY1);
		break;

	case MAP_ICE:
		land_tex1=main_app.GetTextureLoader()->GetTexture(TEX_ICE1);
		land_tex2=main_app.GetTextureLoader()->GetTexture(TEX_ICE2);
		water_tex=main_app.GetTextureLoader()->GetTexture(TEX_WATER1);
		sky_tex=main_app.GetTextureLoader()->GetTexture(TEX_SKY1);
		break;

	case MAP_ROCK:
		land_tex1=main_app.GetTextureLoader()->GetTexture(TEX_ROCK1);
		land_tex2=main_app.GetTextureLoader()->GetTexture(TEX_ROCK2);
		water_tex=main_app.GetTextureLoader()->GetTexture(TEX_WATER1);
		sky_tex=main_app.GetTextureLoader()->GetTexture(TEX_SKY1);
		break;

	case MAP_SAND:
		land_tex1=main_app.GetTextureLoader()->GetTexture(TEX_SAND1);
		land_tex2=main_app.GetTextureLoader()->GetTexture(TEX_SAND2);
		water_tex=main_app.GetTextureLoader()->GetTexture(TEX_WATER1);
		sky_tex=main_app.GetTextureLoader()->GetTexture(TEX_SKY1);
		break;

	default:
		return false;
	}

	fread(&num_vertices,sizeof(int),1,file1);
	fread(&num_triangles,sizeof(int),1,file1);

	vertex = new CVector3f[num_vertices];
	tc = new Texcoord[num_vertices];
	hit = new bool[num_vertices];
	tri = new Triangle[num_triangles];
	tri_sec = new int[num_triangles];
	collision = new int[num_triangles];
	plane = new Plane[num_triangles];
	shade_flat = new t_diffuse[num_triangles];
	shade_gouraud = new t_diffuse[num_vertices];
	light_vertex = new temp_lights[num_vertices];
	test = new CVector3f[num_triangles];

	fread(vertex,sizeof(CVector3f),num_vertices,file1);
	fread(tc,sizeof(Texcoord),num_vertices,file1);
	fread(tri,sizeof(Triangle),num_triangles,file1);
	fclose(file1);

	loaded=true;

	for(int i=0;i<num_vertices;i++)
		hit[i]=false;

	for(i=0;i<MAX_PARTICLE_SOURCES;i++)
		part_source[i].Init(1000,ROCK);

	if(!ReadColorMaps())
		return false;
	CalcAABB();
	CalcPlanesAndShades();
	CreateSectors();

	return true;
}

bool CMap::ReadColorMaps()
{
	int i;
	FILE *file1;

	file1=fopen("textures/grass.col","rb");
	if(!file1)
		return false;
	for(i=0;i<16;i++)
	{
		fread(&grass_col[i],sizeof(t_diffuse),1,file1);
		swap(&grass_col[i].r,&grass_col[i].b);
	}
	fclose(file1);

	file1=fopen("textures/ice.col","rb");
	if(!file1)
		return false;
	for(i=0;i<16;i++)
	{
		fread(&ice_col[i],sizeof(t_diffuse),1,file1);
		swap(&ice_col[i].r,&ice_col[i].b);
	}
	fclose(file1);

	return true;
}

void CMap::DrawSky()
{
	if(!loaded)
		return;

	glLoadMatrixd(main_app.GetCamera()->temp_matrix);

	glColor3ub(255,255,255);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D,sky_tex);

	glBegin(GL_QUADS);

	// front
	glTexCoord2f(0,0);
	glVertex3f(-20,-50,-20);
	glTexCoord2f(1,0);
	glVertex3f( 20,-50,-20);
	glTexCoord2f(1,3);
	glVertex3f( 20, 20,-20);
	glTexCoord2f(0,3);
	glVertex3f(-20, 20,-20);

	// back
	glTexCoord2f(0,0);
	glVertex3f( 20,-50, 20);
	glTexCoord2f(1,0);
	glVertex3f(-20,-50, 20);
	glTexCoord2f(1,3);
	glVertex3f(-20, 20, 20);
	glTexCoord2f(0,3);
	glVertex3f( 20, 20, 20);

	// left
	glTexCoord2f(0,0);
	glVertex3f(-20,-50, 20);
	glTexCoord2f(1,0);
	glVertex3f(-20,-50,-20);
	glTexCoord2f(1,3);
	glVertex3f(-20, 20,-20);
	glTexCoord2f(0,3);
	glVertex3f(-20, 20, 20);

	// right
	glTexCoord2f(0,0);
	glVertex3f( 20,-50,-20);
	glTexCoord2f(1,0);
	glVertex3f( 20,-50, 20);
	glTexCoord2f(1,3);
	glVertex3f( 20, 20, 20);
	glTexCoord2f(0,3);
	glVertex3f( 20, 20,-20);

	// top
	glTexCoord2f(0,0);
	glVertex3f(-20, 20,-20);
	glTexCoord2f(1,0);
	glVertex3f( 20, 20,-20);
	glTexCoord2f(1,1);
	glVertex3f( 20, 20, 20);
	glTexCoord2f(0,1);
	glVertex3f(-20, 20, 20);

	glEnd();

	glEnable(GL_DEPTH_TEST);
}

void CMap::DrawLand()
{
	glPopMatrix();

	if(!loaded)
		return;

	CullSectors(main_app.GetCamera());

	// drawing water
	//glDisable(GL_FOG);
	glBindTexture(GL_TEXTURE_2D,water_tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-16384.0f,16, 16384.0f);
	glTexCoord2f(80.0f,0.0f);
	glVertex3f( 16384.0f,16, 16384.0f);
	glTexCoord2f(80.0f,80.0f);
	glVertex3f( 16384.0f,16,-16384.0f);
	glTexCoord2f(0.0f,80.0f);
	glVertex3f(-16384.0f,16,-16384.0f);
	glEnd();

	if(shademode==NO_SHADE)
		glColor3ub(255,255,255);

	// drawing land

	//glEnable(GL_FOG);

	// drawing unhit triangles
	glBindTexture(GL_TEXTURE_2D,land_tex1);

	glBegin(GL_TRIANGLES);
	for(int i=0;i<num_triangles;i++)
	{
		if(hit[tri[i].vertex[0]] ||
			hit[tri[i].vertex[1]] ||
			hit[tri[i].vertex[2]])
			continue;

		if(!sector[tri_sec[i]].visible)
			continue;

		if(shademode==GOURAUD)
		{
			glColor3ub(shade_gouraud[tri[i].vertex[0]].r,
				shade_gouraud[tri[i].vertex[0]].g,
				shade_gouraud[tri[i].vertex[0]].b);
		}
		else if(shademode==FLAT)
		{
			glColor3ub(shade_flat[i].r,shade_flat[i].g,shade_flat[i].b);
		}
		glTexCoord2f(tc[tri[i].vertex[0]].u,-tc[tri[i].vertex[0]].v);
		glVertex3fv(vertex[tri[i].vertex[0]].xyz);
		if(shademode==GOURAUD)
		{
			glColor3ub(shade_gouraud[tri[i].vertex[1]].r,
				shade_gouraud[tri[i].vertex[1]].g,
				shade_gouraud[tri[i].vertex[1]].b);
		}
		glTexCoord2f(tc[tri[i].vertex[1]].u,-tc[tri[i].vertex[1]].v);
		glVertex3fv(vertex[tri[i].vertex[1]].xyz);
		if(shademode==GOURAUD)
		{
			glColor3ub(shade_gouraud[tri[i].vertex[2]].r,
				shade_gouraud[tri[i].vertex[2]].g,
				shade_gouraud[tri[i].vertex[2]].b);
		}
		glTexCoord2f(tc[tri[i].vertex[2]].u,-tc[tri[i].vertex[2]].v);
		glVertex3fv(vertex[tri[i].vertex[2]].xyz);
	}
	glEnd();

	// drawing hit triangles
	glBindTexture(GL_TEXTURE_2D,land_tex2);

	glBegin(GL_TRIANGLES);
	for(i=0;i<num_triangles;i++)
	{
		if(!hit[tri[i].vertex[0]] &&
			!hit[tri[i].vertex[1]] &&
			!hit[tri[i].vertex[2]])
			continue;

		if(!sector[tri_sec[i]].visible)
			continue;

		if(shademode==GOURAUD)
		{
			glColor3ub(shade_gouraud[tri[i].vertex[0]].r,
				shade_gouraud[tri[i].vertex[0]].g,
				shade_gouraud[tri[i].vertex[0]].b);
		}
		else if(shademode==FLAT)
		{
			glColor3ub(shade_flat[i].r,shade_flat[i].g,shade_flat[i].b);
		}
		glTexCoord2f(tc[tri[i].vertex[0]].u,-tc[tri[i].vertex[0]].v);
		glVertex3fv(vertex[tri[i].vertex[0]].xyz);
		if(shademode==GOURAUD)
		{
			glColor3ub(shade_gouraud[tri[i].vertex[1]].r,
				shade_gouraud[tri[i].vertex[1]].g,
				shade_gouraud[tri[i].vertex[1]].b);
		}
		glTexCoord2f(tc[tri[i].vertex[1]].u,-tc[tri[i].vertex[1]].v);
		glVertex3fv(vertex[tri[i].vertex[1]].xyz);
		if(shademode==GOURAUD)
		{
			glColor3ub(shade_gouraud[tri[i].vertex[2]].r,
				shade_gouraud[tri[i].vertex[2]].g,
				shade_gouraud[tri[i].vertex[2]].b);
		}
		glTexCoord2f(tc[tri[i].vertex[2]].u,-tc[tri[i].vertex[2]].v);
		glVertex3fv(vertex[tri[i].vertex[2]].xyz);
	}
	glEnd();

	// temp
	/*glDisable(GL_TEXTURE_2D);
	glColor3ub(255,0,0);
	for(i=0;i<num_sectors;i++)
	{
		glBegin(GL_LINE_LOOP);
		glVertex3f(sector[i].min_x,0,sector[i].min_z);
		glVertex3f(sector[i].max_x,0,sector[i].min_z);
		glVertex3f(sector[i].max_x,0,sector[i].max_z);
		glVertex3f(sector[i].min_x,0,sector[i].max_z);
		glEnd();
	}

	glEnable(GL_TEXTURE_2D);*/
}

void CMap::CullSectors(Camera *cam)
{
	static CVector3f temp[8];

	for(int i=0;i<num_sectors;i++)
	{
		sector[i].visible=true;

		/*if(player->position.x>sector[i].min_x &&
			player->position.z>sector[i].min_z &&
			player->position.x<sector[i].max_x &&
			player->position.z<sector[i].max_z)
			continue;*/

		temp[0].Set(sector[i].min_x,box_min.xyz[1],sector[i].min_z);
		temp[1].Set(sector[i].max_x,box_min.xyz[1],sector[i].min_z);
		temp[2].Set(sector[i].max_x,box_min.xyz[1],sector[i].max_z);
		temp[3].Set(sector[i].min_x,box_min.xyz[1],sector[i].max_z);
		temp[4].Set(sector[i].min_x,box_max.xyz[1],sector[i].min_z);
		temp[5].Set(sector[i].max_x,box_max.xyz[1],sector[i].min_z);
		temp[6].Set(sector[i].max_x,box_max.xyz[1],sector[i].max_z);
		temp[7].Set(sector[i].min_x,box_max.xyz[1],sector[i].max_z);

		for(int j=0;j<6;j++)
		{
			if(DotProduct(cam->v_frustum[j].normal,temp[0])+cam->v_frustum[j].distance>0)
				continue;

			if(DotProduct(cam->v_frustum[j].normal,temp[1])+cam->v_frustum[j].distance>0)
				continue;

			if(DotProduct(cam->v_frustum[j].normal,temp[2])+cam->v_frustum[j].distance>0)
				continue;

			if(DotProduct(cam->v_frustum[j].normal,temp[3])+cam->v_frustum[j].distance>0)
				continue;

			if(DotProduct(cam->v_frustum[j].normal,temp[4])+cam->v_frustum[j].distance>0)
				continue;

			if(DotProduct(cam->v_frustum[j].normal,temp[5])+cam->v_frustum[j].distance>0)
				continue;

			if(DotProduct(cam->v_frustum[j].normal,temp[6])+cam->v_frustum[j].distance>0)
				continue;

			if(DotProduct(cam->v_frustum[j].normal,temp[7])+cam->v_frustum[j].distance>0)
				continue;

			sector[i].visible=false;
		}
	}
}

int CMap::FindSector(CObject *obj)
{
	for(int i=0;i<num_sectors;i++)
	{
		if(obj->destination.xyz[0]>sector[i].min_x &&
			obj->destination.xyz[2]>sector[i].min_z &&
			obj->destination.xyz[0]<sector[i].max_x &&
			obj->destination.xyz[2]<sector[i].max_z)
			return i;
	}

	return -1;
}

bool CMap::GetCollisionPoint(CVector3f &p,CVector3f &vec,CVector3f *col)
{
	if(!loaded)
		return false;

	CVector3f inter,v[3];
	Plane e_plane;

	int t=0;
	bool co=false;

	for(int i=0;i<num_triangles;i++)
	{
		if(!GetIntersectionPoint_ray_plane(p,vec,plane[i],&inter))
			continue;

		v[0]=vertex[tri[i].vertex[1]]-vertex[tri[i].vertex[0]];
		v[1]=vertex[tri[i].vertex[2]]-vertex[tri[i].vertex[1]];
		v[2]=vertex[tri[i].vertex[0]]-vertex[tri[i].vertex[2]];

		for(int j=0,c=0;j<3;j++)
		{
			e_plane.normal=CrossProduct(v[j],plane[i].normal);
			e_plane.distance=-DotProduct(e_plane.normal,vertex[tri[i].vertex[j]]);

			if((DotProduct(inter,e_plane.normal)+e_plane.distance) <= 0 )
				c++;
		}

		if(c==3) // collision with triangle
		{
			*col=inter;
			//return true;
			co=true;
			test[t++]=inter;
		}
	}

	float d_min=(float)0xffffffff;
	float d;
	int index=0;
	for(i=0;i<t;i++)
	{
		d=GetDistance_pp(test[i],p);
		if(d<d_min)
		{
			d_min=d;
			index=i;
		}
	}

	*col=test[index];

	return co;
	//return false;
}

bool CMap::GetCollisionPoint(CObject *obj,CVector3f *col)
{
	if(!loaded)
		return false;

	CVector3f disp,inter,v[3];
	Plane e_plane;
	float dist1,dist2;
	int s;

	s=FindSector(obj);
	if(s==-1)
		return false;

	disp=obj->destination-obj->position;
	disp.Normalize();

	for(int i=0;i<num_triangles;i++)
	{
		if(tri_sec[i]!=s)
			continue;

		dist1=DotProduct(plane[i].normal,obj->position)+plane[i].distance;
		dist2=DotProduct(plane[i].normal,obj->destination)+plane[i].distance;

		if(!(dist1>0 && dist2<=OBJECT_RADIUS))
			continue;

		if(!GetIntersectionPoint_ray_plane(obj->position,disp,plane[i],&inter))
			continue;

		v[0]=vertex[tri[i].vertex[1]]-vertex[tri[i].vertex[0]];
		v[1]=vertex[tri[i].vertex[2]]-vertex[tri[i].vertex[1]];
		v[2]=vertex[tri[i].vertex[0]]-vertex[tri[i].vertex[2]];

		for(int j=0,c=0;j<3;j++)
		{
			e_plane.normal=CrossProduct(v[j],plane[i].normal);
			e_plane.distance=-DotProduct(e_plane.normal,vertex[tri[i].vertex[j]]);

			if((DotProduct(inter,e_plane.normal)+e_plane.distance) <= OBJECT_RADIUS )
				c++;
		}

		if(c==3) // collision with triangle
		{
			*col=inter;
			return true;
		}
	}

	return false;
}

int CMap::CheckCollision(CObject *obj)
{
	if(!loaded)
		return -1;

	CVector3f disp,inter,v[3];
	Plane e_plane;
	float dist1,dist2;
	int s,triangles=0;

	s=FindSector(obj);
	if(s==-1)
		return -1;

	disp=obj->destination-obj->position;
	disp.Normalize();

	for(int i=0;i<num_triangles;i++)
	{
		if(tri_sec[i]!=s)
			continue;

		dist1=DotProduct(plane[i].normal,obj->position)+plane[i].distance;
		dist2=DotProduct(plane[i].normal,obj->destination)+plane[i].distance;

		if(!(dist1>0 && dist2<OBJECT_RADIUS))
			continue;

		if(!GetIntersectionPoint_ray_plane(obj->position,disp,plane[i],&inter))
			continue;

		v[0]=vertex[tri[i].vertex[1]]-vertex[tri[i].vertex[0]];
		v[1]=vertex[tri[i].vertex[2]]-vertex[tri[i].vertex[1]];
		v[2]=vertex[tri[i].vertex[0]]-vertex[tri[i].vertex[2]];

		for(int j=0,c=0;j<3;j++)
		{
			e_plane.normal=CrossProduct(v[j],plane[i].normal);
			e_plane.distance=-DotProduct(e_plane.normal,vertex[tri[i].vertex[j]]);

			if((DotProduct(inter,e_plane.normal)+e_plane.distance) <= OBJECT_RADIUS )
				c++;
		}

		if(c==3) // collision with triangle
		{
			collision[triangles++]=i;
		}
	}

	return triangles;
}

void CMap::ClipDisplacement(CObject *obj)
{
	if(!loaded)
		return;

	bool calc_force_vec=obj->onground;
	int triangles;
	float d;

	triangles=CheckCollision(obj);

	if(triangles>0)
	{
		for(int i=0;i<triangles;i++)
		{
			obj->onground=true;

			d=DotProduct(plane[collision[i]].normal,
				obj->destination)+plane[collision[i]].distance;
			if(d>=OBJECT_RADIUS)
				continue;
			d=OBJECT_RADIUS-d;

			if(GetAngle_vv(plane[collision[i]].normal,CVector3f(0,1,0))>45.0f)
			{
				obj->destination+=VectorNormalize(plane[collision[i]].normal+(CVector3f(0,1,0)*4))*d;
				//player->onground=false;
			}
			else
				obj->destination+=CVector3f(0,1,0)*d;
		}
	}
	else
	{
		obj->onground=false;

		if(calc_force_vec)
		{
			obj->force_dir=VectorNormalize(obj->destination-obj->position);
			//obj->force_dir.y=0;
		}
	}
}

void CMap::CalcPlanesAndShades()
{
	if(!loaded)
		return;

	CVector3f temp[3];
	float t,layersize;
	unsigned char l;
	int i,j,k,percent;

	for(i=0;i<num_triangles;i++)
	{
		temp[0]=vertex[tri[i].vertex[0]];
		temp[1]=vertex[tri[i].vertex[1]];
		temp[2]=vertex[tri[i].vertex[2]];

		plane[i]=CalcPlane(temp);
	}

	temp[0].Set(0,-1,1);
	temp[0].Normalize();

	for(i=0;i<num_vertices;i++)
	{
		light_vertex[i].l[0]=255;
		light_vertex[i].l[1]=255;
		light_vertex[i].l[2]=255;
		light_vertex[i].l[3]=255;
		light_vertex[i].l[4]=255;
		light_vertex[i].l[5]=255;
		light_vertex[i].count=0;
	}

	layersize=box_max.xyz[1]/16;

	for(i=0;i<num_triangles;i++)
	{
		t=(-DotProduct(plane[i].normal,temp[0])+1)*0.5f;
		//t=-DotProduct(plane[i].normal,temp[0])+1;
		l=unsigned char(t*255);

		light_vertex[tri[i].vertex[0]].l[light_vertex[tri[i].vertex[0]].count++]=l;
		light_vertex[tri[i].vertex[1]].l[light_vertex[tri[i].vertex[1]].count++]=l;
		light_vertex[tri[i].vertex[2]].l[light_vertex[tri[i].vertex[2]].count++]=l;

		// calculating flat shades
		temp[1]=vertex[tri[i].vertex[0]];
		temp[1]+=vertex[tri[i].vertex[1]];
		temp[1]+=vertex[tri[i].vertex[2]];
		temp[1]/=3;

		for(j=0;j<16;j++)
		{
			k=j+1;
			if(temp[1].xyz[1]<=layersize*k && temp[1].xyz[1]>=layersize*j)
			{
				switch(map_type)
				{
				case MAP_GRASS:
					shade_flat[i].r=grass_col[j].r;
					shade_flat[i].g=grass_col[j].g;
					shade_flat[i].b=grass_col[j].b;
					break;

				case MAP_ICE:
					shade_flat[i].r=ice_col[j].r;
					shade_flat[i].g=ice_col[j].g;
					shade_flat[i].b=ice_col[j].b;
					break;

				case MAP_ROCK:
					shade_flat[i].r=rock_col[j].r;
					shade_flat[i].g=rock_col[j].g;
					shade_flat[i].b=rock_col[j].b;
					break;

				case MAP_SAND:
					shade_flat[i].r=sand_col[j].r;
					shade_flat[i].g=sand_col[j].g;
					shade_flat[i].b=sand_col[j].b;
					break;
				}
				break;
			}
		}

		l=255-l;
		percent=int(((float)l/255.0f)*100);

		if(percent!=0)
		{
			shade_flat[i].r-=(shade_flat[i].r*percent)/100;
			shade_flat[i].g-=(shade_flat[i].g*percent)/100;
			shade_flat[i].b-=(shade_flat[i].b*percent)/100;
		}
	}

	// calculating gouraud shades
	for(i=0;i<num_vertices;i++)
	{
		l=(light_vertex[i].l[0]+
			light_vertex[i].l[1]+
			light_vertex[i].l[2]+
			light_vertex[i].l[3]+
			light_vertex[i].l[4]+
			light_vertex[i].l[5])/6;

		for(j=0;j<16;j++)
		{
			k=j+1;
			if(vertex[i].xyz[1]<=layersize*k && vertex[i].xyz[1]>=layersize*j)
			{
				switch(map_type)
				{
				case MAP_GRASS:
					shade_gouraud[i].r=grass_col[j].r;
					shade_gouraud[i].g=grass_col[j].g;
					shade_gouraud[i].b=grass_col[j].b;
					break;

				case MAP_ICE:
					shade_gouraud[i].r=ice_col[j].r;
					shade_gouraud[i].g=ice_col[j].g;
					shade_gouraud[i].b=ice_col[j].b;
					break;

				case MAP_ROCK:
					shade_gouraud[i].r=rock_col[j].r;
					shade_gouraud[i].g=rock_col[j].g;
					shade_gouraud[i].b=rock_col[j].b;
					break;

				case MAP_SAND:
					shade_gouraud[i].r=sand_col[j].r;
					shade_gouraud[i].g=sand_col[j].g;
					shade_gouraud[i].b=sand_col[j].b;
					break;
				}
				break;
			}
		}

		l=255-l;
		percent=int(((float)l/255.0f)*100);

		if(percent!=0)
		{
			shade_gouraud[i].r-=(shade_gouraud[i].r*percent)/100;
			shade_gouraud[i].g-=(shade_gouraud[i].g*percent)/100;
			shade_gouraud[i].b-=(shade_gouraud[i].b*percent)/100;
		}
	}
}

void CMap::DeformGeometry(CVector3f p,float radius)
{
	if(!loaded)
		return;

	float dist;
	CVector3f temp;

	for(int i=0;i<num_vertices;i++)
	{
		if(vertex[i].xyz[1]>p.xyz[1])
		{
			temp=vertex[i];
			temp.xyz[1]=p.xyz[1];
			dist=GetDistance_pp(p,temp);
		}
		else
			dist=GetDistance_pp(p,vertex[i]);
		if(dist < radius)
		{
			if(vertex[i].xyz[1]>p.xyz[1])
				vertex[i].xyz[1]=p.xyz[1];
			dist=GetDistance_pp(p,vertex[i]);
			vertex[i].xyz[1]-=radius-dist;
			if(vertex[i].xyz[1]<0)
				vertex[i].xyz[1]=0;
			hit[i]=true;
		}
	}

	CalcPlanesAndShades();
}

void CMap::SetValidPlayerPositions()
{
	int i;
	float max_y,max_x,max_z,min_x,min_z;
	CGame *game=main_app.GetGame();
	CPlayer *player=game->GetPlayers();
	CVector3f down_vec;

	down_vec.Set(0,-1,0);

	/*max_y=box_max.y+100;
	max_x=box_max.x-100;
	min_x=box_min.x+100;
	max_z=box_max.z-100;
	min_z=box_min.z+100;*/
	max_y=box_max.xyz[1]+100;
	max_x=box_max.xyz[0]*0.75f;
	min_x=box_min.xyz[0]*0.75f;
	max_z=box_max.xyz[2]*0.75f;
	min_z=box_min.xyz[2]*0.75f;

	for(i=0;i<game->GetPlayerCount();i++)
	{
		do
		{
		player[i].Init(
			float(min_x+rand()%int(max_x-min_x+1)),
			//0,
			max_y,
			float(min_z+rand()%int(max_z-min_z+1))
			//0
			);
		}while(!CheckIfValidPlayerPosition(player[i].position,down_vec));
	}
}

bool CMap::CheckIfValidPlayerPosition(CVector3f &p,CVector3f &vec)
{
	if(!loaded)
		return false;

	CVector3f inter,v[3];
	Plane e_plane;

	for(int i=0;i<num_triangles;i++)
	{
		if(!GetIntersectionPoint_ray_plane(p,vec,plane[i],&inter))
			continue;

		v[0]=vertex[tri[i].vertex[1]]-vertex[tri[i].vertex[0]];
		v[1]=vertex[tri[i].vertex[2]]-vertex[tri[i].vertex[1]];
		v[2]=vertex[tri[i].vertex[0]]-vertex[tri[i].vertex[2]];

		for(int j=0,c=0;j<3;j++)
		{
			e_plane.normal=CrossProduct(v[j],plane[i].normal);
			e_plane.distance=-DotProduct(e_plane.normal,vertex[tri[i].vertex[j]]);

			if((DotProduct(inter,e_plane.normal)+e_plane.distance) <= 0 )
				c++;
		}

		if(c==3) // collision with triangle
		{
			if(GetAngle_vv(plane[i].normal,CVector3f(0,1,0))>45.0f)
				return false;

			return true;
		}
	}

	return false;
}

void CMap::CalcAABB()
{
	box_min=box_max=vertex[0];

	for(int i=0;i<num_vertices;i++)
	{
		if(vertex[i].xyz[0]<box_min.xyz[0])
			box_min.xyz[0]=vertex[i].xyz[0];
		if(vertex[i].xyz[1]<box_min.xyz[1])
			box_min.xyz[1]=vertex[i].xyz[1];
		if(vertex[i].xyz[2]<box_min.xyz[2])
			box_min.xyz[2]=vertex[i].xyz[2];
		if(vertex[i].xyz[0]>box_max.xyz[0])
			box_max.xyz[0]=vertex[i].xyz[0];
		if(vertex[i].xyz[1]>box_max.xyz[1])
			box_max.xyz[1]=vertex[i].xyz[1];
		if(vertex[i].xyz[2]>box_max.xyz[2])
			box_max.xyz[2]=vertex[i].xyz[2];
	}
}

void CMap::CreateSectors()
{
	int num_x,num_z;
	int x,z,i;
	float space,inc_x,inc_z;

	space=VERTEX_SPACE*6;
	num_x=int((box_max.xyz[0]-box_min.xyz[0])/(space))+1;
	num_z=int((box_max.xyz[2]-box_min.xyz[2])/(space))+1;

	num_sectors=num_x*num_z;

	sector = new t_sector[num_sectors];

	for(i=0,z=0,inc_z=0;z<num_z;z++,inc_z+=space)
	{
		for(x=0,inc_x=0;x<num_x;i++,x++,inc_x+=space)
		{
			sector[i].min_x=box_min.xyz[0]+inc_x;
			sector[i].min_z=box_min.xyz[2]+inc_z;
			sector[i].max_x=box_min.xyz[0]+inc_x+space;
			sector[i].max_z=box_min.xyz[2]+inc_z+space;
		}
	}

	for(i=0;i<num_triangles;i++)
	{
		CVector3f center;

		center=vertex[tri[i].vertex[0]];
		center+=vertex[tri[i].vertex[1]];
		center+=vertex[tri[i].vertex[2]];
		center/=3;

		for(int j=0;j<num_sectors;j++)
		{
			if(center.xyz[0]>sector[j].min_x &&
				center.xyz[2]>sector[j].min_z &&
				center.xyz[0]<sector[j].max_x &&
				center.xyz[2]<sector[j].max_z) // point/triangle is inside the current sector
			{
				tri_sec[i]=j;
			}
		}
	}
}

int CMap::StartNewParticleSource(float x,float y,float z,float f,bool s)
{
	for(int i=0;i<MAX_PARTICLE_SOURCES;i++)
	{
		if(!part_source[i].active)
		{
			part_source[i].Set(x,y,z);
			part_source[i].Start(f,s);

			return i;
		}
	}

	return -1;
}

void CMap::StopParticleSource(int index)
{
	part_source[index].Stop();
}

void CMap::Update()
{
	for(int i=0;i<MAX_PARTICLE_SOURCES;i++)
	{
		if(part_source[i].active)
			part_source[i].Update();
	}
}

void CMap::DrawStuff()
{
	for(int i=0;i<MAX_PARTICLE_SOURCES;i++)
	{
		if(part_source[i].active)
			part_source[i].Draw();
	}
}

void CMap::Destruct()
{
	for(int i=0;i<MAX_PARTICLE_SOURCES;i++)
	{
		part_source[i].active=false;
		part_source[i].Stop();
	}

	if(vertex)
	{
		delete [] vertex;
		vertex=NULL;
	}
	if(tc)
	{
		delete [] tc;
		tc=NULL;
	}
	if(tri)
	{
		delete [] tri;
		tri=NULL;
	}
	if(tri_sec)
	{
		delete [] tri_sec;
		tri_sec=NULL;
	}
	if(plane)
	{
		delete [] plane;
		plane=NULL;
	}
	if(shade_gouraud)
	{
		delete [] shade_gouraud;
		shade_gouraud=NULL;
	}
	if(shade_flat)
	{
		delete [] shade_flat;
		shade_flat=NULL;
	}
	if(light_vertex)
	{
		delete [] light_vertex;
		light_vertex=NULL;
	}
	if(hit)
	{
		delete [] hit;
		hit=NULL;
	}
	if(sector)
	{
		delete [] sector;
		sector=NULL;
	}
	if(collision)
	{
		delete [] collision;
		collision=NULL;
	}
	if(test)
	{
		delete [] test;
		test=NULL;
	}

	loaded=false;
}
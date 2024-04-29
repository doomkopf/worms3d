#include "CParticleSource.h"
#include "CMain.h"
#include "texload.h"

extern CMain main_app;

CParticleSource::CParticleSource()
{
	loaded=spread=active=false;
}

void CParticleSource::Set(float x,float y,float z)
{
	position.Set(x,y,z);
}

void CParticleSource::Init(int n_particles,t_particle_type type)
{
	num_particles=n_particles;
	particle = new t_particle[num_particles];
	loaded=true;

	texture=main_app.GetTextureLoader()->GetTexture(TEX_PARTICLE_ROCK1);
}

void CParticleSource::InitParticle(int index)
{
	particle[index].force=float((rand()%100)*force)+20*force;
	particle[index].force_dec=float((rand()%7)+3)/25;
	particle[index].position=position;
	particle[index].x_dir=float((rand()%20)*force)-10*force;
	particle[index].z_dir=float((rand()%20)*force)-10*force;
	particle[index].rot_speed=float(rand()%10)+10;
	particle[index].rot_angle=0;
	particle[index].active=true;
}

void CParticleSource::Start(float f,bool s)
{
	force=f;
	spread=s;
	active=true;

	for(int i=0;i<num_particles;i++)
		InitParticle(i);
}

void CParticleSource::Stop()
{
	spread=false;
}

void CParticleSource::Update()
{
	if(!loaded || !active)
		return;

	for(int i=0,c=0;i<num_particles;i++)
	{
		particle[i].force-=main_app.frametime*particle[i].force_dec;
		particle[i].position.xyz[0]+=(particle[i].x_dir*main_app.frametime)*0.05f;
		particle[i].position.xyz[2]+=(particle[i].z_dir*main_app.frametime)*0.05f;
		particle[i].position.xyz[1]+=(particle[i].force*main_app.frametime*0.01f);
		particle[i].rot_angle+=particle[i].rot_speed*main_app.frametime*0.1f;

		if(particle[i].position.xyz[1]<0)
		{
			particle[i].active=false;
			if(spread)
				InitParticle(i);
			c++;
		}
	}
	if(c==num_particles)
		active=false;
}

void CParticleSource::Draw()
{
	if(!loaded || !active)
		return;

	glBindTexture(GL_TEXTURE_2D,texture);
	glDisable(GL_CULL_FACE);
	glColor3ub(255,255,255);
	for(int i=0;i<num_particles;i++)
	{
		if(!particle[i].active)
			continue;
		glPushMatrix();
		glTranslatef(particle[i].position.xyz[0],
			particle[i].position.xyz[1],
			particle[i].position.xyz[2]);
		glRotatef(particle[i].rot_angle,1,1,1);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(1,1);
		glVertex3f(5,5,0);
		glTexCoord2f(0,1);
		glVertex3f(-5,5,0);
		glTexCoord2f(1,0);
		glVertex3f(5,-5,0);
		glTexCoord2f(0,0);
		glVertex3f(-5,-5,0);
		glEnd();
		glPopMatrix();
	}
	glEnable(GL_CULL_FACE);
}

void CParticleSource::Destruct()
{
	if(loaded)
		delete [] particle;
}

CParticleSource::~CParticleSource()
{
	Destruct();
}
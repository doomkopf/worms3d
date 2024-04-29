#ifndef CPARTICLESOURCE
#define CPARTICLESOURCE

#include "defs.h"
#include "math.h"

typedef struct
{
	CVector3f position;
	float force,x_dir,z_dir,force_dec;
	float rot_angle,rot_speed;
	bool active;
} t_particle;

typedef enum
{
	ROCK,BLOOD
} t_particle_type;

class CParticleSource
{
public:
	CParticleSource();
	~CParticleSource();
	void Set(float,float,float);
	void Init(int,t_particle_type);
	void Start(float,bool);
	void Stop();
	void Update();
	void Draw();
	void Destruct();

	bool active;

protected:
	void InitParticle(int);

	t_particle *particle;
	int num_particles;
	CVector3f position;
	float force;
	bool loaded,spread;
	unsigned int texture;
};

#endif
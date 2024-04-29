#include "CAnimObject.h"
#include <windows.h>
#include <gl/gl.h>

void CAnimObject::SetModel(CModelMD2 *m)
{
	model=m;
	got_model=true;
	time=0;
}

void CAnimObject::SetAnimation(int anim)
{
	if(anim==last_anim)
		return;

	switch(anim)
	{
	case IDLE1:
		frame_start=IDLE1_START;
		frame_end=IDLE1_END;
		break;

	case RUN:
		frame_start=RUN_START;
		frame_end=RUN_END;
		break;

	case SHOT_STAND:
		frame_start=SHOT_STAND_START;
		frame_end=SHOT_STAND_END;
		break;

	case SHOT_SHOULDER:
		frame_start=SHOT_SHOULDER_START;
		frame_end=SHOT_SHOULDER_END;
		break;

	case JUMP:
		frame_start=JUMP_START;
		frame_end=JUMP_END;
		break;

	case IDLE2:
		frame_start=IDLE2_START;
		frame_end=IDLE2_END;
		break;

	case SHOT_FALLDOWN:
		frame_start=SHOT_FALLDOWN_START;
		frame_end=SHOT_FALLDOWN_END;
		break;

	case IDLE3:
		frame_start=IDLE3_START;
		frame_end=IDLE3_END;
		break;

	case IDLE4:
		frame_start=IDLE4_START;
		frame_end=IDLE4_END;
		break;

	case CROUCH:
		frame_start=CROUCH_START;
		frame_end=CROUCH_END;
		break;

	case CROUCH_CRAWL:
		frame_start=CROUCH_CRAWL_START;
		frame_end=CROUCH_CRAWL_END;
		break;

	case CROUCH_IDLE:
		frame_start=CROUCH_IDLE_START;
		frame_end=CROUCH_IDLE_END;
		break;

	case CROUCH_DEATH:
		frame_start=CROUCH_DEATH_START;
		frame_end=CROUCH_DEATH_END;
		break;

	case DEATH_FALLBACK:
		frame_start=DEATH_FALLBACK_START;
		frame_end=DEATH_FALLBACK_END;
		break;

	case DEATH_FALLFORWARD:
		frame_start=DEATH_FALLFORWARD_START;
		frame_end=DEATH_FALLFORWARD_END;
		break;

	case DEATH_FALLBACKSLOW:
		frame_start=DEATH_FALLBACKSLOW_START;
		frame_end=DEATH_FALLBACKSLOW_END;
		break;
	}

	frame_cur=frame_start;
	last_anim=anim;
}

void CAnimObject::DrawModel()
{
	//static float time=0;

	if(got_model && drawmodel)
	{
		glColor3ub(255,255,255);
		glPushMatrix();

		glTranslatef(position.xyz[0],position.xyz[1]-8,position.xyz[2]);
		glRotatef(90-yrot,0,1,0);
		glRotatef(90,-1,0,0);
		glScalef(0.5f,0.5f,0.5f);
		model->Render(frame_cur);

		time+=speed;
		if(time>10)
		{
			time=0;
			frame_cur++;
			if(frame_cur>frame_end)
				frame_cur=frame_start;
		}

		glPopMatrix();
	}
}
#include "CRocketLauncher.h"
#include "CMain.h"

extern CMain main_app;

CRocketLauncher::CRocketLauncher()
{
}

void CRocketLauncher::Shoot(CVector3f &pos,CVector3f &vec,bool key_down)
{
	if(main_app.GetControl()->hit[SHOOT])
		main_app.GetGame()->StartNewRocket(pos,vec);
}

void CRocketLauncher::Update()
{
}

void CRocketLauncher::Draw()
{
}
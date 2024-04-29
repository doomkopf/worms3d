#include "CControl.h"
#include <stdio.h>
#include "GLWindow.h"

extern GLWindow win;

bool CControl::Init()
{
	keyboard.InitKeyboard(win.hwnd,GetModuleHandle(NULL));
	mouse.InitMouse(win.hwnd,GetModuleHandle(NULL));

	strcpy(actions[FORWARD],"forward");
	strcpy(actions[BACKWARD],"backward");
	strcpy(actions[LEFT],"left");
	strcpy(actions[RIGHT],"right");
	strcpy(actions[JUMP],"jump");
	strcpy(actions[SHOOT],"shoot");
	strcpy(actions[MENU],"menu");
	strcpy(actions[CAM_NEAR],"cam_near");
	strcpy(actions[CAM_FAR],"cam_far");
	strcpy(actions[NEXT_WEAPON],"next_weapon");
	strcpy(actions[SWITCH_CAM],"switch_cam");
	//strcpy(actions[],"");

	strcpy(keys[KEY_UP],"k_up");
	strcpy(keys[KEY_DOWN],"k_down");
	strcpy(keys[KEY_LEFT],"k_left");
	strcpy(keys[KEY_RIGHT],"k_right");
	strcpy(keys[KEY_RETURN],"k_return");
	strcpy(keys[KEY_RSHIFT],"k_rshift");
	strcpy(keys[KEY_LSHIFT],"k_lshift");
	strcpy(keys[KEY_RCONTROL],"k_rcontrol");
	strcpy(keys[KEY_LCONTROL],"k_lcontrol");
	strcpy(keys[KEY_SPACE],"k_space");
	strcpy(keys[KEY_TAB],"k_tab");
	strcpy(keys[KEY_MLEFT],"k_mleft");
	strcpy(keys[KEY_MRIGHT],"k_mright");
	strcpy(keys[KEY_MMIDDLE],"k_mmiddle");
	strcpy(keys[KEY_MWUP],"k_mwup");
	strcpy(keys[KEY_MWDOWN],"k_mwdown");
	strcpy(keys[KEY_BACKSPACE],"k_backspace");
	strcpy(keys[KEY_LALT],"k_lalt");
	strcpy(keys[KEY_RALT],"k_ralt");
	//strcpy(keys[KEY_],"k_");

	converts[KEY_UP]=DIK_UP;
	converts[KEY_DOWN]=DIK_DOWN;
	converts[KEY_LEFT]=DIK_LEFT;
	converts[KEY_RIGHT]=DIK_RIGHT;
	converts[KEY_RETURN]=DIK_RETURN;
	converts[KEY_RSHIFT]=DIK_RSHIFT;
	converts[KEY_LSHIFT]=DIK_LSHIFT;
	converts[KEY_RCONTROL]=DIK_RCONTROL;
	converts[KEY_LCONTROL]=DIK_LCONTROL;
	converts[KEY_SPACE]=DIK_SPACE;
	converts[KEY_TAB]=DIK_TAB;
	converts[KEY_BACKSPACE]=DIK_BACK;
	converts[KEY_LALT]=DIK_LMENU;
	converts[KEY_RALT]=DIK_RMENU;
	converts[KEY_ESCAPE]=DIK_ESCAPE;
	converts[KEY_F1]=DIK_F1;
	converts[KEY_F2]=DIK_F2;
	converts[KEY_F3]=DIK_F3;
	converts[KEY_F4]=DIK_F4;
	converts[KEY_F5]=DIK_F5;
	converts[KEY_F6]=DIK_F6;
	converts[KEY_F7]=DIK_F7;
	converts[KEY_F8]=DIK_F8;
	converts[KEY_F9]=DIK_F9;
	converts[KEY_F10]=DIK_F10;
	converts[KEY_F11]=DIK_F11;
	converts[KEY_F12]=DIK_F12;
	converts[KEY_1]=DIK_1;
	converts[KEY_2]=DIK_2;
	converts[KEY_3]=DIK_3;
	converts[KEY_4]=DIK_4;
	converts[KEY_5]=DIK_5;
	converts[KEY_6]=DIK_6;
	converts[KEY_7]=DIK_7;
	converts[KEY_8]=DIK_8;
	converts[KEY_9]=DIK_9;
	converts[KEY_0]=DIK_0;
	converts[KEY_A]=DIK_A;
	converts[KEY_B]=DIK_B;
	converts[KEY_C]=DIK_C;
	converts[KEY_D]=DIK_D;
	converts[KEY_E]=DIK_E;
	converts[KEY_F]=DIK_F;
	converts[KEY_G]=DIK_G;
	converts[KEY_H]=DIK_H;
	converts[KEY_I]=DIK_I;
	converts[KEY_J]=DIK_J;
	converts[KEY_K]=DIK_K;
	converts[KEY_L]=DIK_L;
	converts[KEY_M]=DIK_M;
	converts[KEY_N]=DIK_N;
	converts[KEY_O]=DIK_O;
	converts[KEY_P]=DIK_P;
	converts[KEY_Q]=DIK_Q;
	converts[KEY_R]=DIK_R;
	converts[KEY_S]=DIK_S;
	converts[KEY_T]=DIK_T;
	converts[KEY_U]=DIK_U;
	converts[KEY_V]=DIK_V;
	converts[KEY_W]=DIK_W;
	converts[KEY_X]=DIK_X;
	converts[KEY_Y]=DIK_Y;
	converts[KEY_Z]=DIK_Z;
	converts[KEY_INSERT]=DIK_INSERT;
	converts[KEY_DELETE]=DIK_DELETE;
	converts[KEY_POS1]=DIK_HOME;
	converts[KEY_END]=DIK_END;
	converts[KEY_BUP]=DIK_PRIOR;
	converts[KEY_BDOWN]=DIK_NEXT;
	converts[KEY_BRACKET]=DIK_OEM_102;
	converts[KEY_COMMA]=DIK_COMMA;
	converts[KEY_DOT]=DIK_PERIOD;
	converts[KEY_PLUS]=DIK_ADD;
	converts[KEY_MINUS]=DIK_MINUS;
	converts[KEY_STAR]=DIK_MULTIPLY;
	converts[KEY_SLASH]=DIK_SLASH;
	//converts[KEY_]=DIK_;

	mouse_x=mouse_y=0;

	if(!LoadControlData("control.cfg"))
		return false;

	for(int i=0;i<NUM_ACTIONS;i++)
		key[i]=hit[i]=c[i]=false;

	for(i=0;i<NUM_KEYS;i++)
		key_d[i]=hit_d[i]=c_d[i]=false;

	return true;
}

bool CControl::LoadControlData(char *filename)
{
	FILE *file1;
	char str[64],str1[32],str2[32];
	int i,j;

	file1=fopen(filename,"r");
	if(!file1)
		return false;

	for(i=0;i<NUM_KEYS;i++)
		identifiers[i]=-1;

	while(!feof(file1))
	{
		fgets(str,64,file1);

		// reading key
		i=j=0;
		do
		{
			str1[j++]=str[i++];
		} while(str[i]!=' ');
		str1[j]=0;

		i++;

		// reading action
		j=0;
		do
		{
			str2[j++]=str[i++];
		} while(str[i]!=0);
		str2[j-1]=0;

		for(i=0;i<NUM_KEYS;i++)
		{
			for(j=0;j<NUM_ACTIONS;j++)
			{
				if(strcmp(str1,keys[i])==0 && strcmp(str2,actions[j])==0)
				{
					identifiers[i]=j;
					i=NUM_KEYS;
					break;
				}
			}
		}
	}

	fclose(file1);

	return true;
}

void CControl::Update()
{
	keyboard.GetState();
	mouse.GetState();

	// getting mouse movement
	mouse_x=float(mouse.mstate.lX)*0.25f;
	mouse_y=float(mouse.mstate.lY)*0.25f;

	// getting mouse keys
	hit[identifiers[KEY_MLEFT]]=false;
	hit_d[KEY_MLEFT]=false;
	if(mouse.mstate.rgbButtons[0])
	{
		key[identifiers[KEY_MLEFT]]=true;
		key_d[KEY_MLEFT]=true;
		if(!c[identifiers[KEY_MLEFT]])
		{
			c[identifiers[KEY_MLEFT]]=true;
			hit[identifiers[KEY_MLEFT]]=true;
		}
		if(!c_d[KEY_MLEFT])
		{
			c_d[KEY_MLEFT]=true;
			hit_d[KEY_MLEFT]=true;
		}
	}
	else
	{
		key[identifiers[KEY_MLEFT]]=false;
		key_d[KEY_MLEFT]=false;
		c[identifiers[KEY_MLEFT]]=false;
		c_d[KEY_MLEFT]=false;
	}

	hit[identifiers[KEY_MRIGHT]]=false;
	hit_d[KEY_MRIGHT]=false;
	if(mouse.mstate.rgbButtons[1])
	{
		key[identifiers[KEY_MRIGHT]]=true;
		key_d[KEY_MRIGHT]=true;
		if(!c[identifiers[KEY_MRIGHT]])
		{
			c[identifiers[KEY_MRIGHT]]=true;
			hit[identifiers[KEY_MRIGHT]]=true;
		}
		if(!c_d[KEY_MRIGHT])
		{
			c_d[KEY_MRIGHT]=true;
			hit_d[KEY_MRIGHT]=true;
		}
	}
	else
	{
		key[identifiers[KEY_MRIGHT]]=false;
		key_d[KEY_MRIGHT]=false;
		c[identifiers[KEY_MRIGHT]]=false;
		c_d[KEY_MRIGHT]=false;
	}

	hit[identifiers[KEY_MMIDDLE]]=false;
	hit_d[KEY_MMIDDLE]=false;
	if(mouse.mstate.rgbButtons[2])
	{
		key[identifiers[KEY_MMIDDLE]]=true;
		key_d[KEY_MMIDDLE]=true;
		if(!c[identifiers[KEY_MMIDDLE]])
		{
			c[identifiers[KEY_MMIDDLE]]=true;
			hit[identifiers[KEY_MMIDDLE]]=true;
		}
		if(!c_d[KEY_MMIDDLE])
		{
			c_d[KEY_MMIDDLE]=true;
			hit_d[KEY_MMIDDLE]=true;
		}
	}
	else
	{
		key[identifiers[KEY_MMIDDLE]]=false;
		key_d[KEY_MMIDDLE]=false;
		c[identifiers[KEY_MMIDDLE]]=false;
		c_d[KEY_MMIDDLE]=false;
	}

	if(mouse.mstate.lZ>0)
	{
		key[identifiers[KEY_MWUP]]=true;
		key_d[KEY_MWUP]=true;
	}
	else
	{
		key[identifiers[KEY_MWUP]]=false;
		key_d[KEY_MWUP]=false;
	}

	if(mouse.mstate.lZ<0)
	{
		key[identifiers[KEY_MWDOWN]]=true;
		key_d[KEY_MWDOWN]=true;
	}
	else
	{
		key[identifiers[KEY_MWDOWN]]=false;
		key_d[KEY_MWDOWN]=false;
	}

	// getting keyboard keys
	for(int i=0;i<NUM_KEYS;i++)
	{
		if(i==KEY_MLEFT ||
			i==KEY_MRIGHT ||
			i==KEY_MMIDDLE ||
			i==KEY_MWUP ||
			i==KEY_MWDOWN)
			continue;

		hit[identifiers[i]]=false;
		hit_d[i]=false;
		if(keyboard.key[converts[i]])
		{
			key[identifiers[i]]=true;
			key_d[i]=true;
			if(!c[identifiers[i]])
			{
				c[identifiers[i]]=true;
				hit[identifiers[i]]=true;
			}
			if(!c_d[i])
			{
				c_d[i]=true;
				hit_d[i]=true;
			}
		}
		else
		{
			key[identifiers[i]]=false;
			key_d[i]=false;
			c[identifiers[i]]=false;
			c_d[i]=false;
		}
	}
}
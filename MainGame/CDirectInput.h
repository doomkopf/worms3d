#ifndef CDIRECTINPUT
#define CDIRECTINPUT

#define DIRECTINPUT_VERSION 0x0500
#include <dinput.h>
#pragma comment (lib,"dinput.lib")
#pragma comment (lib,"dxguid.lib")

#define MOUSE 0
#define KEYBOARD 1

class CDirectInput
{
public:
	void InitMouse(HWND,HINSTANCE);
	void InitKeyboard(HWND,HINSTANCE);
	~CDirectInput();
	void GetState();
	DIMOUSESTATE mstate;
	BYTE key[256];
protected:
	LPDIRECTINPUT dinput;
	LPDIRECTINPUTDEVICE device;
	int type;
};

#endif
#ifndef CDIRECTINPUT
#define CDIRECTINPUT

#include <dinput.h>
#pragma comment (lib,"dinput8.lib")
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
	LPDIRECTINPUT8 dinput;
	LPDIRECTINPUTDEVICE8 device;
	int type;
};

#endif
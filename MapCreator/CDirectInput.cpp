#include "CDirectInput.h"

void CDirectInput::InitMouse(HWND hwnd,HINSTANCE hinst)
{
	DirectInput8Create(hinst,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&dinput,NULL);
	dinput->CreateDevice(GUID_SysMouse,&device,NULL);
	device->SetDataFormat(&c_dfDIMouse);
	device->SetCooperativeLevel(hwnd,DISCL_EXCLUSIVE|DISCL_FOREGROUND);
	device->Acquire();
	type=MOUSE;
}

void CDirectInput::InitKeyboard(HWND hwnd,HINSTANCE hinst)
{
	DirectInput8Create(hinst,DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&dinput,NULL);
	dinput->CreateDevice(GUID_SysKeyboard,&device,NULL);
	device->SetDataFormat(&c_dfDIKeyboard);
	device->SetCooperativeLevel(hwnd,DISCL_EXCLUSIVE|DISCL_FOREGROUND);
	device->Acquire();
	type=KEYBOARD;
}

CDirectInput::~CDirectInput()
{
	if(device)
		device->Release();
	if(dinput)
		dinput->Release();
}

void CDirectInput::GetState()
{
	switch(type)
	{
	case MOUSE:
		device->GetDeviceState(sizeof(mstate),&mstate);
		break;

	case KEYBOARD:
		device->GetDeviceState(sizeof(key),&key);
		break;
	}
}
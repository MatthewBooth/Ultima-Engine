#pragma once
#define SafeRelease(pInterface) if(pInterface != NULL) {pInterface->Release(); pInterface=NULL;}

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#define KEYDOWN(name, key) (name[key] & 0x80) 
#define MOUSEBUTTONDOWN(key) (key & 0x80)

//Mouse buttons
#define MOUSEBUTTON_LEFT 0
#define MOUSEBUTTON_RIGHT 1
#define MOUSEBUTTON_MIDDLE 2

class cDirectInput
{
public:
	cDirectInput(HWND hWnd, HINSTANCE hInst);
	virtual ~cDirectInput(void);

	void poll();
	bool keyDown(char key);
	bool keyUp(char key);
	bool mouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();

private:
	LPDIRECTINPUT8 m_pDirectInput; 
	LPDIRECTINPUTDEVICE8 m_pKeyboard;
	LPDIRECTINPUTDEVICE8 m_pMouse; 

	char                 m_KeyboardState[256]; 
	DIMOUSESTATE2        m_MouseState;
};

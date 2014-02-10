#include "cDirectInput.h"

cDirectInput::cDirectInput(HWND hWnd, HINSTANCE hInst)
{
	//Create the DirectInput object
	DirectInput8Create(hInst, DIRECTINPUT_VERSION, 
			  IID_IDirectInput8, (void**)&m_pDirectInput, NULL); 
 	
	//KEYBOARD =======================================================================
	//Create the keyboard device object
	m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL) ;

	//Set the data format for the keyboard
	m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);

	//Set the cooperative level for the keyboard
	m_pKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//Acquire the keyboard
	if(m_pKeyboard)
	{
		m_pKeyboard->Acquire(); 
	}


	//MOUSE =======================================================================
	//Create the mouse device object
	m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);

	//Set the data format for the mouse
	m_pMouse->SetDataFormat(&c_dfDIMouse2);

	//Set the cooperative level for the mouse
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//Acquire the mouse
	if(m_pMouse)
	{
		m_pMouse->Acquire(); 
	}
}

cDirectInput::~cDirectInput(void)
{
	//*
	if(m_pKeyboard)
	{
		m_pKeyboard->Unacquire(); 
	}

	if(m_pMouse)
	{
		m_pMouse->Unacquire();
	}
	//*/
	SafeRelease( m_pMouse);
	SafeRelease( m_pKeyboard);	
	SafeRelease( m_pDirectInput);
}

void cDirectInput::poll()
{
	// Poll keyboard.
	HRESULT hr = m_pKeyboard->GetDeviceState(sizeof(m_KeyboardState), (void**)&m_KeyboardState); 
	if( FAILED(hr) )
	{
		// Keyboard lost, zero out keyboard data structure.
		ZeroMemory(m_KeyboardState, sizeof(m_KeyboardState));

		 // Try to acquire for next time we poll.
		hr = m_pKeyboard->Acquire();
	}

	// Poll mouse.
	hr = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&m_MouseState); 
	if( FAILED(hr) )
	{
		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&m_MouseState, sizeof(m_MouseState));

		// Try to acquire for next time we poll.
		hr = m_pMouse->Acquire(); 
	}
}

bool cDirectInput::keyDown(char key)
{
	return (m_KeyboardState[key] & 0x80) != 0;
}

bool cDirectInput::keyUp(char key)
{
	return !((m_KeyboardState[key]) & 0x80);
}

bool cDirectInput::mouseButtonDown(int button)
{
	return (m_MouseState.rgbButtons[button] & 0x80) != 0;
}

float cDirectInput::mouseDX()
{
	return (float)m_MouseState.lX;
}

float cDirectInput::mouseDY()
{
	return (float)m_MouseState.lY;
}

float cDirectInput::mouseDZ()
{
	return (float)m_MouseState.lZ;
}//*/
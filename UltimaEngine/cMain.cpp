#pragma warning(disable : 4996)
#pragma warning(disable : 4800)

#include <Windows.h>
#include <mmsystem.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 

#include "cDirect3D.h"
#include "cBase.h"


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
cDirect3D *mDirect3D = NULL;
cBase *mBase = NULL;
int m_WindowWidth;
int m_WindowHeight;

float					g_fElpasedTime;
double					g_dCurTime;
double					g_dLastTime;

VOID Init()
{
	mBase = new cBase();
	mDirect3D =  new cDirect3D();
	m_WindowWidth = 1024;
	m_WindowHeight = 768;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	delete mDirect3D;
	mBase->~cBase();
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{	
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
		case WM_KEYDOWN:
		switch(wParam)
		{
			case VK_ESCAPE:
				Cleanup();
				PostQuitMessage( 0 );
			return 0;
		}
	}
  return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Init();

	//----------------------------------
    // Register the window class
    WNDCLASSEX wnd;
	ZeroMemory(&wnd, sizeof(WNDCLASSEX));
	wnd.cbSize = sizeof(wnd); 
	wnd.cbClsExtra = 0; 
	wnd.cbWndExtra = 0; 
	wnd.hInstance = GetModuleHandle(0); 
	wnd.lpfnWndProc = MsgProc;
	wnd.lpszClassName = "MAIN_WINDOW";
	wnd.style = CS_VREDRAW | CS_HREDRAW;
	
	if ( !RegisterClassEx(&wnd) )
	{
		MessageBox(NULL, "Failed to register window class", "Registration Failure", MB_OK); 
		return false; 
	}
    // Create the application's window
	HWND hWnd = CreateWindow("MAIN_WINDOW", 
							"Ultima Engine", 
							WS_OVERLAPPEDWINDOW, 
							0, 
							0, 
							mBase->getWindowWidth(), 
							mBase->getWindowHeight(), 
							NULL, 
							NULL, 
							hInstance,
							NULL);
	if (!hWnd) 
	{
		MessageBox(NULL, "Failed to create a window", "Creation Failure", MB_OK); 
			
		return false;
	}
	if( SUCCEEDED( mDirect3D->InitD3D(hWnd, hInstance)))
    { 
            // Show the window
            ShowWindow( hWnd, SW_SHOW );
            UpdateWindow( hWnd );
            // Enter the message loop
            MSG msg; 
            ZeroMemory( &msg, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) != 0 )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                {
                    g_dCurTime     = timeGetTime();
			        g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
			        g_dLastTime    = g_dCurTime;
                    
                    mDirect3D->Render();
                }
            }
    }
 
    return 0;
}
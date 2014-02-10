#pragma once

#include "cCamera.h"
#include "cStaticMesh.h"
#include "cDirectInput.h"
#include "cLight.h"
#include "cFont.h"

class cDirect3D
{
public:
	cDirect3D(void);
	~cDirect3D(void);

	VOID					Render();
	HRESULT					InitD3D(HWND hWnd, HINSTANCE hInst);
	LPDIRECT3DDEVICE9		GetDevice(VOID);

private:
	VOID					Init();
	VOID					SetupMatrices();

	//DirectX objects
	LPDIRECT3D9             g_pD3D;
	LPDIRECT3DDEVICE9       g_pd3dDevice;
	D3DXMATRIXA16			Move, Rotate, Scale, Translation, matSum;
	D3DMATERIAL9			BoundingboxColor;
	D3DXVECTOR3				minB, maxB, obb[8];

	//Camera and Input objects
	cCamera					*mCamera;
	cDirectInput			*mInput;

	// Mesh objects
	cStaticMesh				*mSkyBox;

	cStaticMesh				*mTerrain;

	cStaticMesh				*mCarMesh;
	cStaticMesh				*mRanger1;
	cStaticMesh				*mPlaneMesh;
	cStaticMesh				*myMesh4;

	//Light objects
	cLight					*mSceneLight;
	cLight					*mCarLight_1;
	cLight					*mCarLight_2;

	//UI Elements
	cFont					*mEngineNameFont;
	cFont					*mHeadLightsFont; 
	cFont					*mHeadLightsOnOffFont;
	cFont					*mFogFont;
	cFont					*mFogOnOffFont;

	// Some program constants
	float					kCameraMovementSpeed;
	float					kCameraRotationSpeed;

	float					oldXPos, oldYPos, oldZPos; 
	float					newXPos, newYPos, newZPos; 
	float					movement, Spin;
	int						i;
	float					m_MouseX;
	float					m_MouseY;
	char					buffer[255];

	bool					mFogEnabled;
	bool					mFogKeyDown;
	bool					mHeadlightsKeyDown;
	bool					mHeadlightsEnabled;
};


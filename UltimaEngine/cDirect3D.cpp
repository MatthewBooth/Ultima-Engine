#include "cDirect3D.h"

cDirect3D::cDirect3D(void)
{
	Init();	
}



cDirect3D::~cDirect3D(void)
{
	delete mCamera;

	mCarMesh->~cStaticMesh();

	mRanger01->~cStaticMesh();
	mRanger02->~cStaticMesh();
	mRanger03->~cStaticMesh();
	mRanger04->~cStaticMesh();
	mRanger05->~cStaticMesh();
	mRanger06->~cStaticMesh();
	mRanger07->~cStaticMesh();
	mRanger08->~cStaticMesh();
	mRanger09->~cStaticMesh();
	mRanger10->~cStaticMesh();
	mSkyBox->~cStaticMesh();
	mPlaneMesh->~cStaticMesh();
	myMesh4->~cStaticMesh();

	mSceneLight->~cLight();
	mCarLight_1->~cLight();
	mCarLight_2->~cLight();

	mFogFont->~cFont();
	mFogOnOffFont->~cFont();
	mHeadLightsFont->~cFont();
	mHeadLightsOnOffFont->~cFont();
			
	mInput->~cDirectInput();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

VOID cDirect3D::Init()
{
	//Device
	cDirect3D::g_pD3D						= NULL; // Used to create the D3DDevice
	cDirect3D::g_pd3dDevice					= NULL; // Our rendering device

	//Meshes
	cDirect3D::mSkyBox						= NULL;

	cDirect3D::mCarMesh						= NULL;
	cDirect3D::mRanger01					= NULL;
	cDirect3D::mRanger02					= NULL;
	cDirect3D::mRanger03					= NULL;
	cDirect3D::mRanger04					= NULL;
	cDirect3D::mRanger05					= NULL;
	cDirect3D::mRanger06					= NULL;
	cDirect3D::mRanger07					= NULL;
	cDirect3D::mRanger08					= NULL;
	cDirect3D::mRanger09					= NULL;
	cDirect3D::mRanger10					= NULL;
	cDirect3D::mPlaneMesh					= NULL;
	cDirect3D::myMesh4						= NULL;

	cDirect3D::mTerrain						= NULL;
	
	//Camera and Input
	cDirect3D::mCamera						= NULL;
	cDirect3D::mInput						= NULL; 

	//Lights
	cDirect3D::mSceneLight					= NULL;
	cDirect3D::mCarLight_1					= NULL;
	cDirect3D::mCarLight_2					= NULL;

	//Fonts
	cDirect3D::mEngineNameFont				= NULL;
	cDirect3D::mHeadLightsFont				= NULL;
	cDirect3D::mHeadLightsOnOffFont			= NULL;
	cDirect3D::mFogFont						= NULL;
	cDirect3D::mFogOnOffFont				= NULL;

	// Some program constants
	cDirect3D::kCameraMovementSpeed			= 0.5f;
	cDirect3D::kCameraRotationSpeed			= 0.001f;

	cDirect3D::oldXPos, oldYPos, oldZPos	= 1.0f; 
	cDirect3D::newXPos, newYPos, newZPos	= 1.0f; 
	cDirect3D::movement, Spin				= 1.0f;
	cDirect3D::i							= 0;
	cDirect3D::m_MouseX						= 0.0f;
	cDirect3D::m_MouseY						= 0.0f;

	//Booleans
	mFogEnabled								= FALSE;
	mFogKeyDown								= FALSE;
	mHeadlightsEnabled						= TRUE;
	mHeadlightsKeyDown						= FALSE;
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT cDirect3D::InitD3D(HWND hWnd, HINSTANCE hInst)
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed               = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferWidth        = 1920;
    d3dpp.BackBufferHeight       = 1080;
    d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Turn on the zbuffer
    //g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

    mCamera			= new cCamera(D3DXVECTOR3(0.0f, 0.0f,-15.0f));
	
	mCarMesh		= new cStaticMesh(g_pd3dDevice, "car");
	mRanger01		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger02		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger03		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger04		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger05		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger06		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger07		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger08		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger09		= new cStaticMesh(g_pd3dDevice, "ranger");
	mRanger10		= new cStaticMesh(g_pd3dDevice, "ranger");

	mPlaneMesh		= new cStaticMesh(g_pd3dDevice, "plane");
	myMesh4			= new cStaticMesh(g_pd3dDevice, "plane");


	mSkyBox			= new cStaticMesh(g_pd3dDevice, "lobby_skybox");
	mTerrain		= new cStaticMesh(g_pd3dDevice, "castle");

	mEngineNameFont				= new cFont(g_pd3dDevice);
	mHeadLightsFont				= new cFont(g_pd3dDevice);
	mHeadLightsOnOffFont		= new cFont(g_pd3dDevice);
	mFogFont					= new cFont(g_pd3dDevice);
	mFogOnOffFont				= new cFont(g_pd3dDevice);

	D3DXMatrixIdentity(&Move);
	D3DXMatrixIdentity(&Rotate);
	D3DXMatrixIdentity(&Scale);
	D3DXMatrixIdentity(&matSum);

	mInput			= new cDirectInput(hWnd, hInst);

	mSceneLight		= new cLight(g_pd3dDevice, D3DLIGHT_DIRECTIONAL); 
	mCarLight_1		= new cLight(g_pd3dDevice, D3DLIGHT_SPOT);
	mCarLight_2		= new cLight(g_pd3dDevice, D3DLIGHT_SPOT);

	float fFogStart = 50.0f,fFogEnd = 1000.0f;
	g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE,mFogEnabled);
	g_pd3dDevice->SetRenderState(D3DRS_RANGEFOGENABLE,true);
	g_pd3dDevice->SetRenderState(D3DRS_FOGCOLOR,D3DCOLOR_XRGB(128,128,128));
	g_pd3dDevice->SetRenderState(D3DRS_FOGTABLEMODE,D3DFOG_LINEAR);
	g_pd3dDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD*)(&fFogStart));
	g_pd3dDevice->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&fFogEnd));

	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID cDirect3D::Render()
{
	//Directional Scene lighting
	mSceneLight->EnableSpecular(TRUE);
	mSceneLight->EnableLight(TRUE);
	mSceneLight->SetDirection(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	mSceneLight->SetLightSpecular(0xffffffff);
	mSceneLight->SetLightDiffuse(0xffffffff);
	mSceneLight->SetAmbient(0xffcccccc);
	mSceneLight->SetupLights(0);

	mCarLight_1->EnableSpecular(TRUE);
	mCarLight_1->EnableLight(mHeadlightsEnabled);
	mCarLight_1->SetRange(70.0f);
	mCarLight_1->SetPosition(D3DXVECTOR3(101.0f, -62.0f, 198.0f));
	mCarLight_1->SetDirection(D3DXVECTOR3(3.0f, -1.0f, -0.1f));
	mCarLight_1->SetLightSpecular(0xffffffff);
	mCarLight_2->SetAmbient(0xffff4444);
	mCarLight_1->SetAttenuation(0.0, 0.125f, 0.0f);
	mCarLight_1->SetupLights(1);

	mCarLight_2->EnableSpecular(TRUE);
	mCarLight_2->EnableLight(mHeadlightsEnabled);
	mCarLight_2->SetRange(70.0f);
	mCarLight_2->SetPosition(D3DXVECTOR3(101.0f, -62.0f, 231.0f));
	mCarLight_2->SetDirection(D3DXVECTOR3(3.0f, -1.0f, -0.1f));
	mCarLight_2->SetLightSpecular(0xffffffff);
	mCarLight_2->SetAmbient(0xffff4444);
	mCarLight_2->SetAttenuation(0.0, 0.125f, 0.0f);
	mCarLight_2->SetupLights(2);

	mInput->poll();

	m_MouseX = mInput->mouseDX();
	m_MouseY = mInput->mouseDY();

	// We rotate at a fixed speed.
	mCamera->Yaw(m_MouseX / 800.0f);
	mCamera->Pitch(m_MouseY / 800.0f);

	if( mInput->keyDown(DIK_W) )
		mCamera->MoveForward(kCameraMovementSpeed);
	if( mInput->keyDown(DIK_S) )
		mCamera->MoveForward(-kCameraMovementSpeed);
	if( mInput->keyDown(DIK_D) )
		mCamera->MoveRight(kCameraMovementSpeed);
	if( mInput->keyDown(DIK_A) )
		mCamera->MoveRight(-kCameraMovementSpeed);
	if( mInput->keyDown(DIK_RSHIFT) || mInput->keyDown(DIK_LSHIFT))
	{
		kCameraMovementSpeed			= 3.0f;
	}
	else
	{
		kCameraMovementSpeed			= 0.5f;
	}

	//Toggle fog on and off
	if (mInput->keyDown(DIK_F))
	{
		mFogKeyDown = TRUE;
	}
	if(mFogKeyDown && mInput->keyUp(DIK_F))
	{
		mFogKeyDown = FALSE;
		mFogEnabled = !mFogEnabled;
		g_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, mFogEnabled);
	}

	//Toggle car headlights on and off
	if (mInput->keyDown(DIK_H))
	{
		mHeadlightsKeyDown = TRUE;
	}
	if(mHeadlightsKeyDown && mInput->keyUp(DIK_H))
	{
		mHeadlightsKeyDown = FALSE;
		mHeadlightsEnabled = !mHeadlightsEnabled;	
	}

    // Clear the backbuffer and the zbuffer
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
                         D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
    
    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
		
	//*
	//Create and render the Skybox
	D3DXMATRIX matView, matViewSave, matWorld, matRotate;
 	// Remember the old view matrix
	g_pd3dDevice->GetTransform( D3DTS_VIEW, &matViewSave );
	// Alter the view matrix so its centred for the skybox
	// The -0.4f for the y value is just to lower the horizon slightly - requires experimentation
	matView = matViewSave;
	matView._41 = 0.0f; matView._42 = -0.4f; matView._43 = 0.0f;

	g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );
	// Set a default world matrix
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixRotationY(&matRotate, 1.0f);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotate);

	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld);
	// Disable the z buffer
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
	g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	// Disable lighting
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	// ... Render our skybox as for an x file

	mSkyBox->Render();
	
	// Disable the z buffer
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	// Disable lighting
	g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	// Restore the original view matrix
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &matViewSave );
	//End of Skybob
	//*/

	//Engine name Font
	mEngineNameFont->FontSize(45);
	mEngineNameFont->SetText("Ultima Engine v1.0");
	mEngineNameFont->SetAlignment(DT_LEFT|DT_NOCLIP);
	mEngineNameFont->SetPosition(10, 0, 0, 0);
	mEngineNameFont->SetColor(0xff33b5e5);
	mEngineNameFont->Render();

	//Headlights info font
	mHeadLightsFont->FontSize(30);
	mHeadLightsFont->SetText("Press H to Toggle Car Headlights");
	mHeadLightsFont->SetAlignment(DT_LEFT|DT_NOCLIP);
	mHeadLightsFont->SetPosition(65, 0, 0, 0);
	mHeadLightsFont->SetColor(0xffffffff);
	mHeadLightsFont->Render();

	//Headlights Toggle Text font
	mHeadLightsOnOffFont->FontSize(30);
	mHeadLightsOnOffFont->SetAlignment(DT_LEFT|DT_NOCLIP);
	mHeadLightsOnOffFont->SetPosition(95, 0, 0, 0);
	if(mHeadlightsEnabled)
	{
		mHeadLightsOnOffFont->SetColor(0xff99cc00);
		mHeadLightsOnOffFont->SetText("Headlights ON");
	}
	else
	{
		mHeadLightsOnOffFont->SetColor(0xffff4444);
		mHeadLightsOnOffFont->SetText("Headlights OFF");
	}
	mHeadLightsOnOffFont->Render();

	//Fog info font
	mFogFont->FontSize(30);
	mFogFont->SetText("Press F to Toggle Fog Effects");
	mFogFont->SetAlignment(DT_LEFT|DT_NOCLIP);
	mFogFont->SetPosition(125, 0, 0, 0);
	mFogFont->SetColor(0xffffffff);
	mFogFont->Render();

	//Fog Toggle Text font
	mFogOnOffFont->FontSize(30);
	mFogOnOffFont->SetAlignment(DT_LEFT|DT_NOCLIP);
	mFogOnOffFont->SetPosition(155, 0, 0, 0);
	if(mFogEnabled)
	{
		mFogOnOffFont->SetColor(0xff99cc00);
		mFogOnOffFont->SetText("Fog ON");
	}
	else
	{
		mFogOnOffFont->SetColor(0xffff4444);
		mFogOnOffFont->SetText("Fog OFF");
	}
	mFogOnOffFont->Render();

	//Start of Terrain Mesh
		Scale = mTerrain->SetScale(1.0f, 1.0f, 1.0f);
		Rotate = mTerrain->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mTerrain->SetPosition(-500.0f, 180.0f, -600.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mTerrain->Render();

		Scale = mPlaneMesh->SetScale(1.0f, 1.0f, 1.0f);
		Spin = timeGetTime()/1000.0f;
		Rotate = mPlaneMesh->SetRotation(Spin, 0.0f, 0.0f); 
		Move = mPlaneMesh->SetPosition(100.0f, 0, 5.0f);
		matSum = Scale*Move*Rotate;
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mPlaneMesh->Render();

 	
		//Start of Ranger(s)
		//Ranger 01
		Scale = mRanger01->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger01->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger01->SetPosition(150.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger01->Render();

		//Ranger 02
		Scale = mRanger02->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger02->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger02->SetPosition(148.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger02->Render();

		//Ranger 03
		Scale = mRanger03->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger03->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger03->SetPosition(146.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger03->Render();

		//Ranger 04
		Scale = mRanger04->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger04->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger04->SetPosition(144.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger04->Render();

		//Ranger05
		Scale = mRanger05->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger05->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger05->SetPosition(142.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger05->Render();

		//Ranger 06
		Scale = mRanger06->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger06->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger06->SetPosition(140.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger06->Render();

		//Ranger 07
		Scale = mRanger07->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger07->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger07->SetPosition(138.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger07->Render();

		//Ranger 08
		Scale = mRanger08->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger08->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger08->SetPosition(136.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger08->Render();

		//Ranger 09
		Scale = mRanger09->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger09->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger09->SetPosition(134.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger09->Render();

		//Ranger 10
		Scale = mRanger10->SetScale(0.2f, 0.2f, 0.2f);
		Rotate = mRanger10->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, Spin, 0.0f);
		Move = mRanger10->SetPosition(132.0f, -76.0f, 100.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mRanger10->Render();

 	//Start of car Mesh
		Scale = mCarMesh->SetScale(0.7f, 0.7f, 0.7f);
		Rotate = mCarMesh->SetRotation(0.0f, 0.0f, 0.0f);//(0.0f, 0.0f, Spin);
		Move = mCarMesh->SetPosition(100.0f, -77.0f, 200.0f);
		matSum = Scale*Rotate*Move;
				
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matSum);
		mCarMesh->Render();


		// Setup the world, view, and projection matrices
        SetupMatrices();
        // End the scene

        
	g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );

}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID cDirect3D::SetupMatrices()
{
    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the 
    // origin, and define "up" to be in the y-direction.

	// Get and set the view matrix
	D3DXMATRIX viewMatrix;
	mCamera->CalculateViewMatrix(&viewMatrix);
	g_pd3dDevice->SetTransform( D3DTS_VIEW, &viewMatrix );	

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 20000.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

LPDIRECT3DDEVICE9 cDirect3D::GetDevice(VOID)
{
	return g_pd3dDevice;
}

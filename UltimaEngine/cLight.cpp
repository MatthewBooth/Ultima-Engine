#include "cLight.h"

cLight::cLight(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DLIGHTTYPE LightType)
{
	m3DDevice = g_pd3dDevice;
	mLightType = LightType;

	Init();
}

cLight::~cLight(void)
{

}

VOID cLight::Init()
{
	mIsLightEnabled = FALSE;
	mIsSpecularEnabled = FALSE;
	ZeroMemory( &mtrl, sizeof( D3DMATERIAL9 ) );
	ZeroMemory( &light, sizeof( D3DLIGHT9 ) );

	mLightPositionX = mLightPositionY = mLightPositionZ  = 0.0f;
	mPositionVector = D3DXVECTOR3(0,0,0);
	mDirectionVector = D3DXVECTOR3(0,0,0);
	mAttenuation0 = mAttenuation1 = mAttenuation2 = 0.0f;
	mSpecularColor = D3DXCOLOR(0,0,0,0);
	mDiffuseColor = D3DXCOLOR(0,0,0,0);
	mAmbientColor = D3DXCOLOR(0,0,0,0);
}

VOID cLight::SetupLights(int lightID)
{
	// Set up a material. The material here just has the diffuse and ambient
    // colors set to yellow. Note that only one material can be used at a time.

	mtrl.Diffuse.r = 1.0f;
    mtrl.Diffuse.g = 1.0f;
    mtrl.Diffuse.b = 1.0f;
    mtrl.Diffuse.a = 1.0f;
    mtrl.Ambient.r = 1.0f;
    mtrl.Ambient.g = 1.0f;
    mtrl.Ambient.b = 1.0f;
    mtrl.Ambient.a = 1.0f;

    m3DDevice->SetMaterial( &mtrl );

	switch (mLightType)
	{
	case D3DLIGHT_DIRECTIONAL:
		SetupDirectionalLight(lightID);
		break;
	case D3DLIGHT_POINT:
		SetupPointLight(lightID);
		break;
	case D3DLIGHT_SPOT:
		SetupSpotLight(lightID);
		break;
	default:
		MessageBox( NULL, "Error: No lighting recognised", "Ultima Engine", MB_OK );
		break;
	}

}

VOID cLight::SetupDirectionalLight(int lightID)
{
	m3DDevice->SetRenderState( D3DRS_LIGHTING, mIsLightEnabled );
	m3DDevice->SetRenderState(D3DRS_SPECULARENABLE, mIsSpecularEnabled);

    light.Type = mLightType;
	light.Diffuse = mDiffuseColor;
	light.Ambient	= mAmbientColor;
	light.Specular = mSpecularColor;

	vecDir = mDirectionVector;

    D3DXVec3Normalize( ( D3DXVECTOR3* )&light.Direction, &vecDir );
	light.Range = mRangeValue;

    m3DDevice->SetLight( lightID, &light );
	m3DDevice->LightEnable( lightID, TRUE );
}

VOID cLight::SetupPointLight(int lightID)
{
	m3DDevice->LightEnable( lightID, mIsLightEnabled );

	light.Diffuse		= mDiffuseColor;
	light.Specular		= mSpecularColor;
	light.Ambient		= mAmbientColor;
    light.Type			= mLightType;
	light.Position		= mPositionVector;
    light.Attenuation0	= mAttenuation0;
    light.Attenuation1	= mAttenuation1;
    light.Attenuation2	= mAttenuation2;
	light.Range			= mRangeValue;
    
	m3DDevice->SetLight( lightID, &light );
	
	m3DDevice->SetRenderState(D3DRS_SPECULARENABLE, mIsSpecularEnabled);

}

VOID cLight::SetupSpotLight(int lightID)
{
	m3DDevice->LightEnable( lightID, mIsLightEnabled );
    m3DDevice->SetRenderState( D3DRS_LIGHTING, mIsLightEnabled );

	// Set up our spot light...
	light.Diffuse		= mDiffuseColor;
	light.Ambient		= mAmbientColor;

	light.Specular		= mSpecularColor;

    light.Type			= mLightType;
    light.Position		= mPositionVector;
	light.Direction		= mDirectionVector;
    light.Attenuation0	= mAttenuation0;
    light.Attenuation1	= mAttenuation1;
    light.Attenuation2	= mAttenuation2;
    light.Range			= mRangeValue;

	float g_fTheta      = D3DXToRadian(20.0f);
	float g_fPhi        = D3DXToRadian(40.0f);
	float g_fFalloff    = 1.0f;

    light.Theta        = g_fTheta;
    light.Phi          = g_fPhi;
    light.Falloff      = g_fFalloff;

    m3DDevice->SetLight( lightID, &light );

	m3DDevice->SetRenderState(D3DRS_SPECULARENABLE, mIsSpecularEnabled);

}

VOID cLight::EnableLight(bool value)
{
	mIsLightEnabled = value;
}

VOID cLight::EnableSpecular(bool value)
{
	mIsSpecularEnabled = value;
}

VOID cLight::SetRange(float value)
{
	mRangeValue = value;
}

VOID cLight::SetPosition(D3DXVECTOR3 vector)
{
	mPositionVector = vector;
}

VOID cLight::SetDirection(D3DXVECTOR3 vector)
{
	mDirectionVector = vector;
}

VOID cLight::SetAttenuation(float mAtten0, float mAtten1, float mAtten2)
{
	mAttenuation0 = mAtten0;
	mAttenuation1 = mAtten1;
	mAttenuation2 = mAtten2;
}

VOID cLight::SetLightDiffuse(D3DXCOLOR color)
{
	mDiffuseColor = color;
}

VOID cLight::SetLightSpecular(D3DXCOLOR color)
{
	mSpecularColor = color;
}

VOID cLight::SetAmbient(D3DXCOLOR color)
{
	mAmbientColor = color;
}
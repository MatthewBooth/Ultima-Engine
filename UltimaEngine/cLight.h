#pragma once
#include <d3dx9.h>

class cLight
{
public:
	cLight(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DLIGHTTYPE LightType);
	~cLight(void);

	VOID SetupLights(int lightID);
	VOID EnableLight(bool value);
	VOID EnableSpecular(bool value);
	VOID SetRange(float value);
	VOID SetPosition(D3DXVECTOR3 vector);
	VOID SetDirection(D3DXVECTOR3 vector );
	VOID SetAttenuation(float mAtten0, float mAtten1, float mAtten2);
	VOID SetLightDiffuse(D3DXCOLOR color);
	VOID SetLightSpecular(D3DXCOLOR color);
	VOID SetAmbient(D3DXCOLOR color);
	
private:

	VOID SetupDirectionalLight(int lightID);
	VOID SetupPointLight(int lightID);
	VOID SetupSpotLight(int lightID);
	VOID Init();

	LPDIRECT3DDEVICE9 m3DDevice;
	D3DLIGHTTYPE mLightType;
	D3DMATERIAL9 mtrl;
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;

	D3DXVECTOR3 mPositionVector;
	D3DXVECTOR3 mDirectionVector;

	D3DXCOLOR mDiffuseColor;
	D3DXCOLOR mSpecularColor;
	D3DXCOLOR mAmbientColor;

	bool mIsLightEnabled;
	bool mIsSpecularEnabled;
	float mRangeValue;
	float mLightPositionX, mLightPositionY, mLightPositionZ;
	float mAttenuation0, mAttenuation1, mAttenuation2;
};
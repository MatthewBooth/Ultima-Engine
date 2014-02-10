#pragma warning(disable : 4996)
#pragma warning(disable : 4800)

#include <d3dx9.h>
#include <strsafe.h>

class cStaticMesh
{
public:

	cStaticMesh(LPDIRECT3DDEVICE9 pD3DDevice, LPSTR pFilename);
	~cStaticMesh(void);

	bool					Render();
	D3DXMATRIXA16			SetPosition(float x, float y, float z);
	D3DXMATRIXA16			SetRotation(float x, float y, float z);
	D3DXMATRIXA16			SetScale(float x, float y, float z);
	D3DXMATRIXA16			SetTranslation(float x, float y, float z);

	LPD3DXMESH				getMesh();
	float					getPosition_X();
	float					getPosition_Y();
	float					getPosition_Z();

private:
	HRESULT					InitMesh();
	LPSTR					concatSTR(LPSTR str1, LPSTR str2);

	LPDIRECT3DDEVICE9		m3DDevice;

	LPD3DXMESH              g_pMesh;			// Our mesh object in sysmem
	D3DMATERIAL9*           g_pMeshMaterials;	// Materials for our mesh
	LPDIRECT3DTEXTURE9*     g_pMeshTextures;	// Textures for our mesh
	DWORD                   g_dwNumMaterials;   // Number of mesh materials
	LPD3DXBUFFER			pD3DXMtrlBuffer;	// Materials Buffer

	LPSTR					mMeshFilename;
	LPSTR					mMeshFilenameNoExtension;
	LPSTR					mMeshFilenameInParentFolder;

	float					posX;
	float					posY;
	float					posZ;
};
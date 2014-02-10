#include "cStaticMesh.h"

//-----------------------------------------------------------------------------
// Name: cStaticMesh()
// Desc: The class Constructor
//-----------------------------------------------------------------------------
cStaticMesh::cStaticMesh(LPDIRECT3DDEVICE9 pD3DDevice, LPSTR pFilename)
{
	m3DDevice = pD3DDevice;

	//Picking the meshes from their individual folders
	cStaticMesh::mMeshFilenameNoExtension = pFilename;
	cStaticMesh::mMeshFilename = concatSTR(pFilename, ".x");
	cStaticMesh::mMeshFilenameInParentFolder = concatSTR(concatSTR("Models/", concatSTR(mMeshFilenameNoExtension, "/")), mMeshFilename);

	InitMesh();

}

//-----------------------------------------------------------------------------
// Name: ~cStaticMesh()
// Desc: The class deconstructor
//-----------------------------------------------------------------------------
cStaticMesh::~cStaticMesh(void)
{
	if( g_pMeshMaterials != NULL ) 
        delete[] g_pMeshMaterials;

    if( g_pMeshTextures )
    {
        for( DWORD i = 0; i < g_dwNumMaterials; i++ )
        {
            if( g_pMeshTextures[i] )
                g_pMeshTextures[i]->Release();
        }
        delete[] g_pMeshTextures;
    }
    if( g_pMesh != NULL )
        g_pMesh->Release();
}

//-----------------------------------------------------------------------------
// Name: InitMesh()
// Desc: Initialises the Mesh
//-----------------------------------------------------------------------------
HRESULT cStaticMesh::InitMesh()
{
	
	LPD3DXBUFFER pD3DXMtrlBuffer;

    // Load the mesh from the specified file
    if( FAILED( D3DXLoadMeshFromX( mMeshFilename, D3DXMESH_SYSTEMMEM,
                                   m3DDevice, NULL,
                                   &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
                                   &g_pMesh ) ) )
    {
        // If model is not in current folder, try parent folder
		if( FAILED( D3DXLoadMeshFromX( mMeshFilenameInParentFolder, D3DXMESH_SYSTEMMEM,
                                       m3DDevice, NULL,
                                       &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
                                       &g_pMesh ) ) )
        {
			MessageBox( NULL, concatSTR("Could not find Mesh: ", mMeshFilename), "Ultima Engine", MB_OK );
            return E_FAIL;
        }
    }

    // We need to extract the material properties and texture names from the 
    // pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBuffer->GetBufferPointer();
    g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
    if( g_pMeshMaterials == NULL )
        return E_OUTOFMEMORY;
    g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
    if( g_pMeshTextures == NULL )
        return E_OUTOFMEMORY;

    for( DWORD i = 0; i < g_dwNumMaterials; i++ )
    {
        // Copy the material
        g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

        g_pMeshTextures[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
        {
            // Create the texture
            if( FAILED( D3DXCreateTextureFromFileA( m3DDevice,
                                                    d3dxMaterials[i].pTextureFilename,
                                                    &g_pMeshTextures[i] ) ) )
            {
                // If texture is not in current folder, try parent folder
				const CHAR* strPrefix = concatSTR(concatSTR("Models/", mMeshFilenameNoExtension), "/");
                CHAR strTexture[MAX_PATH];
                strcpy_s( strTexture, MAX_PATH, strPrefix );
                strcat_s( strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename );
                // If texture is not in current folder, try parent folder
                if( FAILED( D3DXCreateTextureFromFileA( m3DDevice,
                                                        strTexture,
                                                        &g_pMeshTextures[i] ) ) )
                {
					MessageBox( NULL, concatSTR("Could not find texture map for: ", mMeshFilename), "Ultima Engine", MB_OK );
                }
            }
        }
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Renders the mesh
//-----------------------------------------------------------------------------
bool cStaticMesh::Render()
{
	if(g_pMesh != NULL)
	{
        // Meshes are divided into subsets, one for each material. Render them in
        // a loop
        for( DWORD i=0; i<g_dwNumMaterials; i++ )
        {
            // Set the material and texture for this subset
            m3DDevice->SetMaterial( &g_pMeshMaterials[i] );
            m3DDevice->SetTexture( 0, g_pMeshTextures[i] );
        
            // Draw the mesh subset
            g_pMesh->DrawSubset( i );
        }

		return g_pMesh->GetNumFaces();
	}
	else
	{
		return 0;
	}
}

D3DXMATRIXA16 cStaticMesh::SetPosition(float x, float y, float z)
{
	D3DXMATRIX matMove;

	D3DXMatrixTranslation(&matMove, x, y, z);

	posX = x;
	posY = y;
	posZ = z;
	
	//m3DDevice->SetTransform(D3DTS_WORLD, &matMove);

	return matMove;
}

D3DXMATRIXA16 cStaticMesh::SetRotation(float x, float y, float z)
{
	D3DXMATRIX matRotate;

	D3DXMatrixRotationYawPitchRoll (&matRotate, x, y, z);

	return matRotate;
}

D3DXMATRIXA16 cStaticMesh::SetScale(float x, float y, float z)
{
	D3DXMATRIX matScale;

	D3DXMatrixScaling(&matScale, x, y, z);

	return matScale;
}

D3DXMATRIXA16 cStaticMesh::SetTranslation(float x, float y, float z)
{
	D3DXMATRIX matTranslation;

	D3DXMatrixTranslation(&matTranslation, x, y, z);

	return matTranslation;
}

LPD3DXMESH cStaticMesh::getMesh()
{
	return g_pMesh;
}

float cStaticMesh::getPosition_X()
{
	return posX;
}

float cStaticMesh::getPosition_Y()
{
	return posY;
}

float cStaticMesh::getPosition_Z()
{
	return posZ;
}

LPSTR cStaticMesh::concatSTR(LPSTR str1, LPSTR str2)
{
      char* str = new char[strlen(str1) + strlen(str2) + 1];
      LPSTR final_str = str;
 
      strcpy(str, str1);
      strcat(str, str2);
      return final_str;
}
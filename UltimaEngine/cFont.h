#pragma once
#include <d3dx9.h>

class cFont
{
public:
	cFont(LPDIRECT3DDEVICE9 device);
	~cFont(void);

	VOID				Render();
	VOID				SetText(LPSTR text);
	VOID				SetAlignment(BYTE alignment);
	VOID				SetPosition(int top, int bottom, int left, int right);
	VOID				SetColor(D3DCOLOR color);
	VOID				FontSize(int size);

	LPSTR				mText;
	BYTE				mAlignment;
	int					mTop, mBottom, mLeft, mRight;
	int					mFontSize;
	D3DCOLOR			mColor;

private:

	VOID				Init();

	LPD3DXFONT			m_Font;
	RECT				mFontPos;
	LPDIRECT3DDEVICE9	pD3DDevice;

	
};


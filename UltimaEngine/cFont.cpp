#include "cFont.h"


cFont::cFont(LPDIRECT3DDEVICE9 device)
{
	pD3DDevice = device;
}


cFont::~cFont(void)
{
	if(m_Font != NULL)
	 {
		m_Font->Release(); //release font
		m_Font = NULL;
	 }
}

VOID cFont::Init()
{
	m_Font = NULL;
	D3DXFONT_DESC  mFontDesc = { mFontSize, 
		0, 
		400, 
		1, 
		false, 
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS, 
		ANTIALIASED_QUALITY, 
		DEFAULT_PITCH|FF_DONTCARE, 
		"Arial" };
	
	mFontPos.top = 0;
	mFontPos.left = 0;
	mFontPos.right = 1024;
	mFontPos.bottom = 768;

	//create font
	D3DXCreateFontIndirect(pD3DDevice, &mFontDesc, &m_Font);
}

VOID cFont::SetText(LPSTR text)
{
	mText = text;
}
VOID cFont::SetAlignment(BYTE alignment)
{
	mAlignment = alignment;
}
VOID cFont::SetPosition(int top, int bottom, int left, int right)
{
	mTop = top;
	mBottom = bottom;
	mLeft = left;
	mRight = right;
}
VOID cFont::SetColor(D3DCOLOR color)
{
	mColor = color;
}

VOID cFont::FontSize(int size)
{
	mFontSize = size;
}

VOID cFont::Render()
{
	Init();
	//Position
	mFontPos.top = mTop;

	//Draw the text
	m_Font->DrawText(NULL, mText, -1, &mFontPos, mAlignment, mColor);

	if(m_Font != NULL)
	 {
		m_Font->Release(); //release font
		m_Font = NULL;
	 }
}


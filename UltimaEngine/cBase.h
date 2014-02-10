#pragma warning(disable : 4996)
#pragma warning(disable : 4800)

#include <d3dx9.h>
#include <strsafe.h>

class cBase
{
public:
	cBase(void);
	~cBase(void);

	LPSTR						concatSTR(LPSTR str1, LPSTR str2);
	INT	static					getWindowHeight();
	INT	static					getWindowWidth();
	LPSTR static				getEngineName();						

};


#include "cBase.h"


cBase::cBase(void)
{
}


cBase::~cBase(void)
{
}

LPSTR cBase::concatSTR(LPSTR str1, LPSTR str2)
{
      char* str = new char[strlen(str1) + strlen(str2) + 1];
      LPSTR final_str = str;
 
      strcpy(str, str1);
      strcat(str, str2);
      return final_str;
}

INT cBase::getWindowHeight()
{
	return 768;
}

INT cBase::getWindowWidth()
{
	return 1024;
}

LPSTR cBase::getEngineName()
{
	return "Ultima Engine";
}
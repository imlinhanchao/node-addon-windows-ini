#include "common.h"

char * _strcpy(const char* szSrc, char* szDst) 
{
	while(*szSrc){ 
		*szDst++ = *szSrc++;
	}
	*szDst = 0;
	return szDst;
}
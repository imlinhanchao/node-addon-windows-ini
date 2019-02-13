#ifndef _GV_INIFILE_H_
#define _GV_INIFILE_H_

#include "common.h"

class Ini
{

public:
	Ini(const TCHAR* pszIniFile/*full path*/);

	void SetFile(const TCHAR* pszIniFile/*full path*/);

	bool GetAllKeys(TCHAR* pszAppName, TCHAR* pszKeys[], int& nCount);
	bool GetAllApps(TCHAR* pszAppName[], int& nCount);

	// read ini
	bool Read(TCHAR*  pszAppName, TCHAR*  pszKeyName, TCHAR*   pszValue, int nMaxSize=1024);
	
	// write ini
	bool Write(TCHAR*  pszAppName, TCHAR*  pszKeyName, TCHAR*  pszValue);

	bool Remove(TCHAR* pszAppName, TCHAR* pszKeyName);
	bool Remove(TCHAR* pszAppName);

private:
	TCHAR m_szIni[MAX_PATH];
};

#endif


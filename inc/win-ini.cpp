#include "win-ini.h"

Ini::Ini(const TCHAR* pszIniFile)
{
	SetFile(pszIniFile);
}

void Ini::SetFile(const TCHAR* pszIniFile/*full path*/)
{
	memcpy(m_szIni, pszIniFile, sizeof(TCHAR) * MAX_PATH);
}

bool Ini::GetAllKeys(TCHAR* pszAppName, TCHAR* pszKeys[], int& nCount)
{
	const int nBufferSize = 10000;
	TCHAR szValue[nBufferSize] = {0};
	int nTCHARSize = 0;
	if(0 != (nTCHARSize = GetPrivateProfileString(pszAppName, NULL, NULL, szValue, nBufferSize, m_szIni)))
	{
		int nIndex = 0;
		_strcpy(szValue, pszKeys[nIndex]);
		for (int nPos = 0; nPos < nTCHARSize; nPos++)
		{
			if (szValue[nPos] == '\0')
			{
				nIndex++;
				if (nIndex >= nCount) continue;
				_strcpy(szValue + nPos + 1, pszKeys[nIndex]);
			}
		}
		nCount = nIndex;
		return true;
	}

	nCount = 0;

	return false;
}

bool Ini::GetAllApps(TCHAR* pszKeys[], int& nCount)
{
	const int nBufferSize = 10000;
	TCHAR szValue[nBufferSize] = {0};
	int nTCHARSize = 0;
	if(0 != (nTCHARSize = GetPrivateProfileSectionNames(szValue, nBufferSize, m_szIni)))
	{
		int nIndex = 0;
		_strcpy(szValue, pszKeys[nIndex]);
		for (int nPos = 0; nPos < nTCHARSize; nPos++)
		{
			if (szValue[nPos] == '\0')
			{
				nIndex++;
				if (nIndex >= nCount) continue;
				_strcpy(szValue + nPos + 1, pszKeys[nIndex]);
			}
		}
		nCount = nIndex;
		return true;
	}

	nCount = 0;

	return false;
}

bool Ini::Read(TCHAR *pszAppName, TCHAR* pszKeyName, TCHAR* pszValue, int nMaxSize)
{
	if(0 != GetPrivateProfileString(pszAppName, pszKeyName, NULL, pszValue, nMaxSize, m_szIni))
	{
		return true;
	}

	return false;
}

bool Ini::Write(TCHAR* pszAppName, TCHAR* pszKeyName, TCHAR* pszValue)
{
	if(WritePrivateProfileString(pszAppName, pszKeyName, pszValue, m_szIni))
	{
		return true;
	}

	return false;
}

bool Ini::Write(TCHAR* pszAppName, TCHAR* pszKeyName, bool bValue)
{
	if(WritePrivateProfileString(pszAppName, pszKeyName, bValue ? _T("1") : _T("0"), m_szIni))
	{
		return true;
	}

	return false;
}

bool Ini::Remove(TCHAR* pszAppName, TCHAR* pszKeyName)
{
	if(WritePrivateProfileString(pszAppName, pszKeyName, NULL, m_szIni))
	{
		return true;
	}
	return false;
}

bool Ini::Remove(TCHAR* pszAppName)
{
	return Remove(pszAppName, NULL);
}


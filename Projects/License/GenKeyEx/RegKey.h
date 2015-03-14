#if !defined(AFX_REGKEY_H__INCLUDED_)
#define AFX_REGKEY_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegKey 
{
	public:
		// Static functions
		static CString GetRegNo(LPCTSTR szPurchaseId, LPCTSTR szRunningNo);
		static CString GetPassword(LPCTSTR szRegNo, LPCTSTR szRegName);
		static CString GetMessage(LPCTSTR szRegNo, LPCTSTR szRegName, LPCTSTR szKey);
		static CString GetShortMessage(LPCTSTR szRegNo, LPCTSTR szRegName, LPCTSTR szKey);

		static int DecKey(LPCTSTR szRegNo, LPCTSTR szRegName, LPCTSTR szKey, LPTSTR szKeyMsg);

		// Static variables
		static LPCTSTR szSecret;
		static LPCTSTR szMessage;
};

#endif // !defined(AFX_REGKEY_H__INCLUDED_)

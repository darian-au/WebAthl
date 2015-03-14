#if !defined(AFX_GENKEYEX_H__INCLUDED_)
#define AFX_GENKEYEX_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

int __stdcall GenKeyEx(LPTSTR argv[], LPTSTR szKeyMsg, LPTSTR szKey);
int __stdcall DecKeyEx(LPTSTR argv[], LPTSTR szKeyMsg);

#endif // !defined(AFX_GENKEYEX_H__INCLUDED_)

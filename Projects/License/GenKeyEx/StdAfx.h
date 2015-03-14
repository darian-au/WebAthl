// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__INCLUDED_)
#define AFX_STDAFX_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



// Insert your headers here
//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

//#include <windows.h>



#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

// There are functions in Windows 95 OEM Service Release 2 that are guarded 
// by (_WIN32_WINNT >= 0x0400), such as the Crypto API. If you are writing 
// an application specifically for Windows 95 OEM Service Release 2, and 
// you want the header files to provide compile time access to these 
// functions, it is necessary to define _WIN32_WINNT as 0x0400. Note that 
// an application that uses these functions will not run correctly on the 
// retail release of Windows 95. In general, applications expected to run 
// on Windows 95 should be built without defining _WIN32_WINNT.

#define _WIN32_WINNT 0x0400	// Enables Cryptographic Functions

#include <wincrypt.h>		// Cryptographic Functions

#include <iostream>
using namespace std;

// TODO: reference additional headers your program requires here

#include "key_intf.h"

#include "MIMECode.h"
#include "Base64.h"
#include "Crypt.h"
#include "CryptByteArray.h"
#include "Switch.h"


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__INCLUDED_)

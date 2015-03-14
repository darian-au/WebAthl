// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include <afxdb.h>			// MFC ODBC database classes
#include <afxisapi.h>		// MFC ISAPI support
#include <afx.h>

#include <afxdisp.h>		// MFC OLE automation classes (COleDateTime)

#include <afxtempl.h>		// MFC templates and collection classes (CMap)

#define _WIN32_WINNT 0x0400	// Enables Cryptographic Functions

#include <wincrypt.h>		// Cryptographic Functions

#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "BulkCopy.h"
#include "StringLine.h"
#include "MIMECode.h"
#include "Base64.h"
#include "Crypt.h"
#include "CryptByteArray.h"
#include "Registry.h"
#include "Properties.h"
#include "HttpServerVariable.h"
#include "HttpServerVariableEx.h"
#include "HttpServerProperties.h"
#include "Util.h"
#include "HtmlMonth.h"
#include "HtmlWriter.h"
#include "Calculate.h"
#include "Convert.h"
#include "Format.h"
#include "BitMaskEnum.h"
#include "Module.h"
#include "Authenticator.h"
#include "PersonSearcher.h"
#include "DBTable.h"
#include "DBView.h"
#include "DBForeignKey.h"
#include "RuleType.h"
#include "RuleSubType.h"
#include "ProcessGroup.h"
#include "Process.h"
#include "MaintainDatabase.h"
#include "FixDuplicateOption.h"
#include "ReportParticipantHistoryOption.h"
#include "ReportFinancialHistoryOption.h"
#include "ReportResultsOption.h"
#include "ReportRosterOption.h"
#include "ReportAwardsOption.h"
#include "ReportPersonOption.h"
#include "ReportResultsBySeriesOption.h"
#include "ReportEventCalendarOption.h"
#include "ReportClubRecordsOption.h"
#include "ReportGroupsListOption.h"
#include "Page.h"
#include "HtmlKey.h"
#include "key_intf.h"
#include "RegKey.h"

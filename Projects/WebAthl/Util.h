#if !defined(AFX_UTIL_H__INCLUDED_)
#define AFX_UTIL_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CUtil.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUtil

class CUtil
{

	public:

		// Constructor
		//CUtil( );	

		// Destructor
		//~CUtil( );

		// Member functions

		// Static functions
		static BOOL LoadLongResource(CString& str, UINT nID);

		static CString AppendFolder(CString strPath, int nInitNum, ...);
		static BOOL CreateFolders(CHttpServerProperties* pProp);

		static CString MakeFolderDatabase(CString strBackupFolder, CString strDatabase);
		static CString MakeFolderData(CString strBackupFolder, CString strDatabase);
		static CString MakeFolderLog(CString strBackupFolder, CString strDatabase);
		static CString MakeFolderError(CString strBackupFolder, CString strDatabase);

		static CString GetFolderDatabase(CHttpServerProperties* pProp);
		static CString GetFolderData(CHttpServerProperties* pProp);
		static CString GetFolderLog(CHttpServerProperties* pProp);
		static CString GetFolderError(CHttpServerProperties* pProp);


		static CString ParseHttpPostQuery(CString strQuerys, TCHAR chDelimiter);

		static int Max(int nCount, ...);

		static int Count(CDatabase* db, LPCTSTR szSQL);

		static int GetIntegerItems(CDatabase* db, LPCTSTR szSQL, CStringArray* strItems);

		static CMap<int,int,CPoint,CPoint>* FindEventsBetweenDates(
			LPCTSTR szConnect,
			COleDateTime dateEventFrom,
			COleDateTime dateEventTo,
			CStringArray* strSeriesIDItems,
			CString* strError);

		// Static variables

		// Member variables

	private:

		// Member variables
};

#endif // !defined(AFX_UTIL_H__INCLUDED_)

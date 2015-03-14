#if !defined(AFX_MAINTAINDATABASE_H__INCLUDED_)
#define AFX_MAINTAINDATABASE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CMaintainDatabase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMaintainDatabase

class CMaintainDatabase : public CBitMaskEnum
{

	public:

		// Constructor
		CMaintainDatabase( );	

		// Destructor
		//~CMaintainDatabase( );

		// Member functions
		virtual CString GetName();
		virtual CString GetTitle();
		virtual CString GetMessage();

		// Static functions
		static CString GetName(DWORD dwItem);
		static CString GetTitle(DWORD dwItem);
		static CString GetMessage(DWORD dwItem);

		// Member variables

		// Static variables
		static enum MaintainDatabaseEnum  // bit mask
		{
			none					= 0x00000000,
			CreateTables			= 0x00000001,
			CreateViews				= 0x00000002,
			ExportData				= 0x00000004,
			ImportData				= 0x00000008,
			CreateForeignKeys		= 0x00000010,
			DropForeignKeys			= 0x00000020,
//			CreateStoredProcedures	= 0x00000040,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_MAINTAINDATABASE_H__INCLUDED_)

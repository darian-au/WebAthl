#if !defined(AFX_REPORTROSTEROPTION_H__INCLUDED_)
#define AFX_REPORTROSTEROPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportRosterOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportRosterOption

class CReportRosterOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportRosterOption( );	

		// Destructor
		//~CReportRosterOption( );

		// Member functions
		virtual CString GetName();
		virtual DWORD GetDefaultSelect();
		virtual CString GetLabel();
		virtual DWORD GetPermission();

		// Static functions
		static CString GetName(DWORD dwItem);
		static DWORD GetDefaultSelect(DWORD dwItem);
		static CString GetLabel(DWORD dwItem);
		static DWORD GetPermission(DWORD dwItem);

		// Member variables

		// Static variables
		static enum ReportRosterOptionEnum  // bit mask
		{
			none						= 0x00000000,
			DisplayTaskDescription		= 0x00000001,
			DisplayPersonID				= 0x00000002,
			DisplayLastName				= 0x00000004,
			DisplayFirstName			= 0x00000008,
			DisplayMiddleName			= 0x00000010,
			DisplaySexAgeGroup			= 0x00000020,
			DisplayDOB					= 0x00000040,
			DisplayAddress				= 0x00000080,
			DisplayTown					= 0x00000100,
			DisplayState				= 0x00000200,
			DisplayPostCode				= 0x00000400,
			DisplayCountry				= 0x00000800,
			DisplayPhoneHm				= 0x00001000,
			DisplayPhoneWk				= 0x00002000,
			DisplayFax					= 0x00004000,
			DisplayMobile				= 0x00008000,
			DisplayEmail				= 0x00010000,
			DisplayContactPersonID		= 0x00020000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTROSTEROPTION_H__INCLUDED_)

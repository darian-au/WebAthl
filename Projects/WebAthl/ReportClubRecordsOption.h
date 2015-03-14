#if !defined(AFX_REPORTCLUBRECORDSOPTION_H__INCLUDED_)
#define AFX_REPORTCLUBRECORDSOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportClubRecordsOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportClubRecordsOption

class CReportClubRecordsOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportClubRecordsOption( );	

		// Destructor
		//~CReportClubRecordsOption( );

		// Member functions
		virtual CString GetName();
		virtual DWORD GetDefaultSelect();
		virtual CString GetLabel();

		// Static functions
		static CString GetName(DWORD dwItem);
		static DWORD GetDefaultSelect(DWORD dwItem);
		static CString GetLabel(DWORD dwItem);

		// Member variables

		// Static variables
		static enum ReportClubRecordsOptionEnum  // bit mask
		{
			none						= 0x00000000,
			DisplayDate					= 0x00000001,
			DisplayEventNo				= 0x00000002,
			DisplayLocationDescription	= 0x00000004,
			DisplayEventDescription		= 0x00000008,
			DisplayPersonID				= 0x00000010,
			DisplayLastName				= 0x00000020,
			DisplayFirstName			= 0x00000040,
			DisplaySexAgeGroup			= 0x00000080,
			DisplayClubPerformance		= 0x00000100,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTCLUBRECORDSOPTION_H__INCLUDED_)

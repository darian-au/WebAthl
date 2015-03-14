#if !defined(AFX_REPORTFINANCIALHISTORYOPTION_H__INCLUDED_)
#define AFX_REPORTFINANCIALHISTORYOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportFinancialHistoryOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportFinancialHistoryOption

class CReportFinancialHistoryOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportFinancialHistoryOption( );	

		// Destructor
		//~CReportFinancialHistoryOption( );

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
		static enum ReportFinancialHistoryOptionEnum  // bit mask
		{
			none							= 0x00000000,
			DisplayDateRenewed				= 0x00000001,
			DisplayYear						= 0x00000002,
			DisplayRegistrationID			= 0x00000004,
			DisplayRegistrationDescription	= 0x00000008,
			DisplayMonthStopStart			= 0x00000010,
			DisplayMailListFlag				= 0x00000020,
			DisplayOrgName					= 0x00000040,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTFINANCIALHISTORYOPTION_H__INCLUDED_)

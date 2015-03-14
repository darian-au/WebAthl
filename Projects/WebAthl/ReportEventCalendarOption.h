#if !defined(AFX_REPORTEVENTCALENDAROPTION_H__INCLUDED_)
#define AFX_REPORTEVENTCALENDAROPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportEventCalendarOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportEventCalendarOption

class CReportEventCalendarOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportEventCalendarOption( );	

		// Destructor
		//~CReportEventCalendarOption( );

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
		static enum ReportEventCalendarOptionEnum  // bit mask
		{
			none					= 0x00000000,
			DisplaySeriesDesc		= 0x00000001,
			DisplayEventNo			= 0x00000002,
			DisplayLocationDesc		= 0x00000004,
			DisplayEventDesc		= 0x00000008,
			DisplayEventDate		= 0x00000010,
			DisplayPreEntryOpen		= 0x00000020,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTEVENTCALENDAROPTION_H__INCLUDED_)

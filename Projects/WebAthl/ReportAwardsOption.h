#if !defined(AFX_REPORTAWARDSOPTION_H__INCLUDED_)
#define AFX_REPORTAWARDSOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportAwardsOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportAwardsOption

class CReportAwardsOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportAwardsOption( );	

		// Destructor
		//~CReportAwardsOption( );

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
		static enum ReportAwardsOptionEnum  // bit mask
		{
			none								= 0x00000000,
			DisplayPersonID						= 0x00000001,
			DisplayLastName						= 0x00000002,
			DisplayFirstName					= 0x00000004,
			DisplaySexAgeGroup					= 0x00000008,
			DisplayDivisionSupposedTo			= 0x00000010,
			DisplayGroupIDSupposedTo			= 0x00000020,
			DisplayEventsForSeason				= 0x00000040,
			DisplayEventsForSeries				= 0x00000080,
			DisplayConsistencyAgeGroup			= 0x00000100,
			DisplayConsistencyEventsCurrent		= 0x00000200,
			DisplayConsistencyEventsOlder		= 0x00000400,
			DisplayConsistencyEventsRate		= 0x00000800,
			DisplayConsistencyAgeStandard		= 0x00001000,
			DisplayGrossPoints					= 0x00002000,
			DisplayNetPoints					= 0x00004000,
			DisplayLowPoints					= 0x00008000,
			DisplayEligibilityForEvent			= 0x00010000,
			DisplayOrgName						= 0x00020000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTAWARDSOPTION_H__INCLUDED_)

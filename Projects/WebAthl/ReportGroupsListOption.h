#if !defined(AFX_REPORTGROUPSLISTOPTION_H__INCLUDED_)
#define AFX_REPORTGROUPSLISTOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportGroupsListOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportGroupsListOption

class CReportGroupsListOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportGroupsListOption( );	

		// Destructor
		//~CReportGroupsListOption( );

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
		static enum ReportGroupsListOptionEnum  // bit mask
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
			DisplayNetPoints					= 0x00000100,
			DisplayEligibilityForEvent			= 0x00000200,
			DisplayGroupStart					= 0x00000400,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTGROUPSLISTOPTION_H__INCLUDED_)

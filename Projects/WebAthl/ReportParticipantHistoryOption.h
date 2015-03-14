#if !defined(AFX_REPORTPARTICIPANTHISTORYOPTION_H__INCLUDED_)
#define AFX_REPORTPARTICIPANTHISTORYOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportParticipantHistoryOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportParticipantHistoryOption

class CReportParticipantHistoryOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportParticipantHistoryOption( );	

		// Destructor
		//~CReportParticipantHistoryOption( );

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
		static enum ReportParticipantHistoryOptionEnum  // bit mask
		{
			none						= 0x00000000,
			DisplaySeriesDescription	= 0x00000001,
			DisplayEventNo				= 0x00000002,
			DisplayDate					= 0x00000004,
			DisplayLocationDescription	= 0x00000008,
			DisplayEventDescription		= 0x00000010,
			DisplayDivisionActual		= 0x00000020,
			DisplayDivisionSupposedTo	= 0x00000040,
			DisplayAgeGroup				= 0x00000080,
			DisplayGroupIDActual		= 0x00000100,
			DisplayGroupIDSupposedTo	= 0x00000200,
			DisplayGroupStartActual		= 0x00000400,
			DisplayGrossPerformance		= 0x00000800,
			DisplayNetPerformance		= 0x00001000,
			DisplayPlace				= 0x00002000,
			DisplayOverallPlace			= 0x00004000,
			DisplayPercentile			= 0x00008000,
			DisplayPoints				= 0x00010000,
			DisplayEligible				= 0x00020000,
			DisplayEventRate			= 0x00040000,
			DisplayGroupRateActual		= 0x00080000,
			DisplayChestNumber			= 0x00100000,
			DisplayWorldStandard		= 0x00200000,
			DisplayNewGroupID			= 0x00400000,
			DisplayNewGroupMessage		= 0x00800000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTPARTICIPANTHISTORYOPTION_H__INCLUDED_)

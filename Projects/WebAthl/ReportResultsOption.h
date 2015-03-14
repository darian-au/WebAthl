#if !defined(AFX_REPORTRESULTSOPTION_H__INCLUDED_)
#define AFX_REPORTRESULTSOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportResultsOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportResultsOption

class CReportResultsOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportResultsOption( );	

		// Destructor
		//~CReportResultsOption( );

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
		static enum ReportResultsOptionEnum  // bit mask
		{
			none					= 0x00000000,
			DisplayDivisionAct		= 0x00000001,
			DisplayDivision			= 0x00000002,
			DisplayOverallPlace		= 0x00000004,
			DisplayPlace			= 0x00000008,
			DisplayPersonID			= 0x00000010,
			DisplayFirstName		= 0x00000020,
			DisplayLastName			= 0x00000040,
			DisplayAgeGroup			= 0x00000080,
			DisplayGroup			= 0x00000100,
			DisplayGroupAct			= 0x00000200,
			DisplayGroupStart		= 0x00000400,
			DisplayGrossPerformance	= 0x00000800,
			DisplayNetPerformance	= 0x00001000,
			DisplayEventRate		= 0x00002000,
			DisplayGroupRate		= 0x00004000,
			DisplayWAVA				= 0x00008000,
			DisplayPoints			= 0x00010000,
			DisplayPercentile		= 0x00020000,
			DisplayEligible			= 0x00040000,
			DisplayNewGroupMsg		= 0x00080000,
			DisplayNewGroup			= 0x00100000,
			DisplayOrganisation		= 0x00200000,
			DisplayChestNumber		= 0x00400000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTRESULTSOPTION_H__INCLUDED_)

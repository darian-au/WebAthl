#if !defined(AFX_REPORTRESULTSBYSERIESOPTION_H__INCLUDED_)
#define AFX_REPORTRESULTSBYSERIESOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportResultsBySeriesOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportResultsBySeriesOption

class CReportResultsBySeriesOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportResultsBySeriesOption( );	

		// Destructor
		//~CReportResultsBySeriesOption( );

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
		static enum ReportResultsBySeriesOptionEnum  // bit mask
		{
			none					= 0x00000000,
			DisplaySeriesDesc		= 0x00000001,
			DisplayEventNo			= 0x00000002,
			DisplayLocationDesc		= 0x00000004,
			DisplayEventDesc		= 0x00000008,
			DisplayEventDate		= 0x00000010,
			DisplayDivisionAct		= 0x00000020,
			DisplayDivision			= 0x00000040,
			DisplayOverallPlace		= 0x00000080,
			DisplayPlace			= 0x00000100,
			DisplayPersonID			= 0x00000200,
			DisplayFirstName		= 0x00000400,
			DisplayLastName			= 0x00000800,
			DisplayAgeGroup			= 0x00001000,
			DisplayGroup			= 0x00002000,
			DisplayGroupAct			= 0x00004000,
			DisplayGroupStart		= 0x00008000,
			DisplayGrossPerformance	= 0x00010000,
			DisplayNetPerformance	= 0x00020000,
			DisplayEventRate		= 0x00040000,
			DisplayGroupRate		= 0x00080000,
			DisplayWAVA				= 0x00100000,
			DisplayPoints			= 0x00200000,
			DisplayPercentile		= 0x00400000,
			DisplayEligible			= 0x00800000,
			DisplayNewGroupMsg		= 0x01000000,
			DisplayNewGroup			= 0x02000000,
			DisplayOrganisation		= 0x04000000,
			DisplayChestNumber		= 0x08000000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTRESULTSBYSERIESOPTION_H__INCLUDED_)

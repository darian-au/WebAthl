#if !defined(AFX_REPORTPERSONOPTION_H__INCLUDED_)
#define AFX_REPORTPERSONOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CReportPersonOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportPersonOption

class CReportPersonOption : public CBitMaskEnum
{

	public:

		// Constructor
		CReportPersonOption( );	

		// Destructor
		//~CReportPersonOption( );

		// Member functions
		virtual CString GetName();
		virtual DWORD GetDefaultSelect();
		virtual CString GetLabel();
		virtual DWORD GetPermission();
		virtual CString GetDescription();

		// Static functions
		static CString GetName(DWORD dwItem);
		static DWORD GetDefaultSelect(DWORD dwItem);
		static CString GetLabel(DWORD dwItem);
		static DWORD GetPermission(DWORD dwItem);
		static CString GetDescription(DWORD dwItem);

		// Member variables

		// Static variables
		static enum ReportPersonOptionEnum  // bit mask
		{
			none						= 0x00000000,
			DisplayPersonID				= 0x00000001,
			DisplayLastName				= 0x00000002,
			DisplayFirstName			= 0x00000004,
			DisplayMiddleName			= 0x00000008,
			DisplayAgeGroup				= 0x00000010,
			DisplayDOB					= 0x00000020,
			DisplayAddress				= 0x00000040,
			DisplayTown					= 0x00000080,
			DisplayState				= 0x00000100,
			DisplayPostCode				= 0x00000200,
			DisplayCountry				= 0x00000400,
			DisplayPhoneHm				= 0x00000800,
			DisplayPhoneWk				= 0x00001000,
			DisplayFax					= 0x00002000,
			DisplayMobile				= 0x00004000,
			DisplayEmail				= 0x00008000,
			DisplayContactPersonID		= 0x00010000,
			DisplayDateRenewed			= 0x00020000,
			DisplayYear					= 0x00040000,
			DisplayRegistrationID		= 0x00080000,
			DisplayRegistrationTypeID	= 0x00100000,
			DisplayMonthStartStop		= 0x00200000,
			DisplayMailListFlag			= 0x00400000,
			DisplayOrgName				= 0x00800000,
			DisplayComments				= 0x01000000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_REPORTPERSONOPTION_H__INCLUDED_)

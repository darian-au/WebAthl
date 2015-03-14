#if !defined(AFX_FIXDUPLICATEOPTION_H__INCLUDED_)
#define AFX_FIXDUPLICATEOPTION_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CFixDuplicateOption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFixDuplicateOption

class CFixDuplicateOption : public CBitMaskEnum
{

	public:

		// Constructor
		CFixDuplicateOption( );	

		// Destructor
		//~CFixDuplicateOption( );

		// Member functions
		virtual CString GetName();
		virtual DWORD GetDefaultSelect();
		virtual CString GetDescription();
		virtual BOOL GetHidden();
	
		// Static functions
		static CString GetName(DWORD dwItem);
		static DWORD GetDefaultSelect(DWORD dwItem);
		static CString GetDescription(DWORD dwItem);
		static BOOL GetHidden(DWORD dwItem);

		// Member variables

		// Static variables
		static enum FixDuplicateOptionEnum  // bit mask
		{
			none						= 0x00000000,
			DeletePersonComments		= 0x00000001,
			DeleteRoster				= 0x00000002,
			DeleteEventRecord			= 0x00000004,
			DeleteParticipantForSeries	= 0x00000008,
			DeleteResults				= 0x00000010,
			DeletePostResults			= 0x00000020,
			DeletePreResults			= 0x00000040,
			DeleteFinancial				= 0x00000080,
			DeleteSecurityPerson		= 0x00000100,
			DeleteSecurityPersonSeries	= 0x00000200,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_FIXDUPLICATEOPTION_H__INCLUDED_)

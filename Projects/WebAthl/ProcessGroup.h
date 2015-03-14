#if !defined(AFX_PROCESSGROUP_H__INCLUDED_)
#define AFX_PROCESSGROUP_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CProcessGroup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcessGroup

class CProcessGroup : public CBitMaskEnum
{

	public:

		// Constructor
		CProcessGroup( );	

		// Destructor
		//~CProcessGroup( );

		// Member functions
		virtual CString GetName();

		// Static functions
		static CString GetName(DWORD dwItem);

		// Member variables

		// Static variables
		static enum ProcessGroupEnum  // bit mask
		{
			none				= 0x00000000,
			PreResults			= 0x00000001,
			PreEvent			= 0x00000002,
			LockOut				= 0x00000004,
			PostEvent			= 0x00000008,
			ClubRecords			= 0x00000010,
			Admin				= 0x00000020,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_PROCESSGROUP_H__INCLUDED_)

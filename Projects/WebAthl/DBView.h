#if !defined(AFX_DBVIEW_H__INCLUDED_)
#define AFX_DBVIEW_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDBView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBView

class CDBView : public CBitMaskEnum
{

	public:

		// Constructor
		CDBView( );	

		// Destructor
		//~CDBView( );

		// Member functions
		virtual CString GetName();
		virtual UINT GetId();

		// Static functions
		static CString GetName(DWORD dwItem);
		static UINT GetId(DWORD dwItem);

		// Member variables

		// Static variables
		static enum DBViewEnum  // bit mask
		{
			none				= 0x00000000,
			LatestFinancial		= 0x00000001,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_DBVIEW_H__INCLUDED_)

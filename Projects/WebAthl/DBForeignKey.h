#if !defined(AFX_DBFOREIGNKEY_H__INCLUDED_)
#define AFX_DBFOREIGNKEY_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDBForeignKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBForeignKey

class CDBForeignKey : public CBitMaskEnum
{

	public:

		// Constructor
		CDBForeignKey( );	

		// Destructor
		//~CDBForeignKey( );

		// Member functions
		virtual CString GetName();
		virtual UINT GetId();
		virtual UINT GetIdDrop();

		// Static functions
		static CString GetName(DWORD dwItem);
		static UINT GetId(DWORD dwItem);
		static UINT GetIdDrop(DWORD dwItem);

		// Member variables

		// Static variables
		static enum DBForeignKeyEnum  // bit mask
		{
			none					= 0x00000000,
//			Series					= 0x00000000,
			SeriesSeason			= 0x00000001,
//			Person					= 0x00000000,
//			EventType				= 0x00000000,
//			Location				= 0x00000000,
			Event					= 0x00000002,
			EventRecord				= 0x00000004,
			WorldStandard			= 0x00000008,
//			Organisation			= 0x00000000,
//			RegistrationType		= 0x00000000,
			Financial				= 0x00000010,
			Groups					= 0x00000020,
			ParticipantForSeries	= 0x00000040,
			PersonComments			= 0x00000080,
//			RosterDescriptions		= 0x00000000,
			Roster					= 0x00000100,
//			RuleType				= 0x00000000,
			RuleSubType				= 0x00000200,
			Rules					= 0x00000400,
//			SecurityRole			= 0x00000000,
			SecurityPerson			= 0x00000800,
			SecurityPersonSeries	= 0x00001000,
			PreResults				= 0x00002000,
			PostResults				= 0x00004000,
			Results					= 0x00008000,
		};



	private:

		// Member variables

};

#endif // !defined(AFX_DBFOREIGNKEY_H__INCLUDED_)

#if !defined(AFX_DBTABLE_H__INCLUDED_)
#define AFX_DBTABLE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CDBTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBTable

class CDBTable : public CBitMaskEnum
{

	public:

		// Constructor
		CDBTable( );	

		// Destructor
		//~CDBTable( );

		// Member functions
		virtual CString GetName();
		virtual UINT GetId();

		// Static functions
		static CString GetName(DWORD dwItem);
		static UINT GetId(DWORD dwItem);

		// Member variables

		// Static variables
		static enum DBTableEnum  // bit mask
		{
			none					= 0x00000000,
			Series					= 0x00000001,
			SeriesSeason			= 0x00000002,
			Person					= 0x00000004,
			EventType				= 0x00000008,
			Location				= 0x00000010,
			Event					= 0x00000020,
			EventRecord				= 0x00000040,
			WorldStandard			= 0x00000080,
			Organisation			= 0x00000100,
			RegistrationType		= 0x00000200,
			Financial				= 0x00000400,
			Groups					= 0x00000800,
			ParticipantForSeries	= 0x00001000,
			PersonComments			= 0x00002000,
			RosterDescriptions		= 0x00004000,
			Roster					= 0x00008000,
			RuleType				= 0x00010000,
			RuleSubType				= 0x00020000,
			Rules					= 0x00040000,
			SecurityRole			= 0x00080000,
			SecurityPerson			= 0x00100000,
			SecurityPersonSeries	= 0x00200000,
			PreResults				= 0x00400000,
			PostResults				= 0x00800000,
			Results					= 0x01000000,
		};



	private:

		// Member variables

};

#endif // !defined(AFX_DBTABLE_H__INCLUDED_)

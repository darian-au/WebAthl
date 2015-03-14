#if !defined(AFX_MODULE_H__INCLUDED_)
#define AFX_MODULE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CModule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModule

class CModule : public CBitMaskEnum
{

	public:

		// Constructor
		CModule( );	

		// Destructor
		//~CModule( );

		// Member functions
		virtual CString GetName();
		virtual CString GetLabel();

		// Static functions
		static CString GetName(DWORD dwItem);
		static CString GetLabel(DWORD dwItem);

		// Member variables

		// Static variables
		static enum ModuleEnum  // bit mask
		{
			none				= 0x00000000,
			Reports				= 0x00000001,
			Financial			= 0x00000002,
			WorldStandards		= 0x00000004,
			ResultsEntry		= 0x00000008,
			RosterDescriptions	= 0x00000010,
			Roster				= 0x00000020,
			Organisation		= 0x00000040,
			Person				= 0x00000080,
			SearchPerson		= 0x00000100,
			EditPerson			= 0x00000200,
			ViewPerson			= 0x00000400,
			Location			= 0x00000800,
			EventType			= 0x00001000,
			Event				= 0x00002000,
			Processing			= 0x00004000,
			RegistrationType	= 0x00008000,
			SeriesMaintain		= 0x00010000,
			SelectSeries		= 0x00020000,
			Security			= 0x00040000,
			Groups				= 0x00080000,
			Rules				= 0x00100000,
			OpenPreEntry		= 0x00200000,
			SeriesAdd			= 0x00400000,
			Utilities			= 0x00800000,
			Options				= 0x01000000,
			Maintenance			= 0x02000000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_MODULE_H__INCLUDED_)

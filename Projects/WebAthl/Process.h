#if !defined(AFX_PROCESS_H__INCLUDED_)
#define AFX_PROCESS_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CProcess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcess

class CProcess : public CBitMaskEnum
{

	public:

		// Constructor
		CProcess( );	

		// Destructor
		//~CProcess( );

		// Member functions
		virtual CString GetName();
		virtual CString GetShortName();
		virtual DWORD GetGroup();

		virtual bool IsMember(DWORD dwGroup);
		
		// Static functions
		static CString GetName(DWORD dwItem);
		static CString GetShortName(DWORD dwItem);
		static DWORD GetGroup(DWORD dwItem);

		// Member variables

		// Static variables
		static enum ProcessEnum  // bit mask
		{
			// This Order is Important
			none							= 0x00000000,
			PadPreResults					= 0x00000001,
			ClosePreEntry					= 0x00000002, 
			PostEventProcessAll				= 0x00000004,
			ClearNewGroup					= 0x00000008,
			PadPostResults					= 0x00000010,
			SetDivisionEligibility			= 0x00000020,
			SetGroupsEligibility			= 0x00000040,
			SetFinancialEligibility			= 0x00000080,
			SetOverAllPlace					= 0x00000100,

//			SetMiscResults					= 0x00000200,

			SetNetPerformance				= 0x00000200,
			SetPercentile					= 0x00000400,
			SetPoints						= 0x00000800,
			SetEventRate					= 0x00001000,

			SetWorldStandards				= 0x00002000,
			ReGroup							= 0x00004000,
			PreEventProcessAll				= 0x00008000,
			RebuildParticipantForSeries		= 0x00010000,
			SetPointScore					= 0x00020000,
			SetConsistencyEventsRate		= 0x00040000,
			SetConsistencyAgeStandard		= 0x00080000,
			SetConsistencyAgeGroup			= 0x00100000,
			SetEventsForSeason				= 0x00200000,

			SetEventsForSeries				= 0x00400000,

			ReSetEligibility				= 0x00800000,
			SetEligibilityXMore				= 0x01000000,
			SetSeriesFinancialEligibility	= 0x02000000,
			LockOut							= 0x04000000,
			RebuildClubRecords				= 0x08000000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_PROCESS_H__INCLUDED_)

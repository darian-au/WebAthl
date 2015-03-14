#if !defined(AFX_PROCESSOR_H__INCLUDED_)
#define AFX_PROCESSOR_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CProcessor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProcessor

class CProcessor
{

	public:

		// Constructor
		//CProcessor( );	

		// Destructor
		//~CProcessor( );

		// Member functions

		// Static functions

		static BOOL CanProcess(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			int iSeriesID,
			int iEventID);

		static BOOL Execute(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);

		// Member variables

		// Static variables

	private:

		// Static functions

		static void ShowProcessMessage(CHtmlWriter* pHtml,
			DWORD dwProc, int iSeriesID, int iEventID);

		static void ShowResultMessage(CHtmlWriter* pHtml,
			int iCount, CString strComment);

//		static BOOL ExecuteDeleteParticipantForSeries(
//			CHtmlWriter* pHtml, 
//			LPCTSTR szConnect, 
//			DWORD dwTimeOut,
//			DWORD dwProc,
//			int iSeriesID,
//			int iEventID);
		static BOOL ExecuteClearNewGroup(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteLockOut(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteReSetEligibility(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetEligibilityXMore(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteRebuildParticipantForSeries(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetDivisionEligibility(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetGroupsEligibility(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecutePadPreResults(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteClosePreEntry(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecutePadPostResults(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetPointScore(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetOverAllPlace(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);

//		static BOOL ExecuteSetMiscResults(
//			CHtmlWriter* pHtml, 
//			LPCTSTR szConnect, 
//			DWORD dwTimeOut,
//			DWORD dwProc,
//			int iSeriesID,
//			int iEventID);

		static BOOL ExecuteSetNetPerformance(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetPercentile(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetPoints(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetEventRate(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);

		static BOOL ExecuteSetWorldStandards(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetConsistencyEventsRate(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetConsistencyAgeStandard(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetConsistencyAgeGroup(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetEventsForSeason(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetEventsForSeries(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteReGroup(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteRebuildClubRecords(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetFinancialEligibility(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);
		static BOOL ExecuteSetSeriesFinancialEligibility(
			CHtmlWriter* pHtml, 
			LPCTSTR szConnect, 
			DWORD dwTimeOut,
			DWORD dwProc,
			int iSeriesID,
			int iEventID);

		static int GetNewGroupID(CHtmlWriter* pHtml,
			CDatabase* pdb,
			int iSeriesID,
			int iEventID,
			int iPersonID,
			int iTimed,
			int iDivisionActual,
			double dEventRate,
			double dGroupStartActual,
			int iGrossPerformanceHOUR,
			int iGrossPerformanceMIN,
			double dGrossPerformanceSEC,
			int iNetPerformanceHOUR,
			int iNetPerformanceMIN,
			double dNetPerformanceSEC);

		// Member variables

};

#endif // !defined(AFX_PROCESSOR_H__INCLUDED_)

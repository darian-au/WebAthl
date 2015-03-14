#if !defined(AFX_CALCULATE_H__INCLUDED_)
#define AFX_CALCULATE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CCalculate.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalculate

class CCalculate
{

	public:

		// Constructor
		//CCalculate( );	

		// Destructor
		//~CCalculate( );

		// Member functions

		// Static functions
		static int YearDiff(int nDay, int nMonth, int nYear);
		static int YearDiff(int nDay1, int nMonth1, int nYear1, int nDay2, int nMonth2, int nYear2);

		static int GroupAge(int nAge, CString& strCategory, CHttpServerProperties* pProp);
		static int GroupAge(int nAge, CString& strCategory, CHttpServerProperties* pProp, int nMaxJunior, int nMinVeteran, int nJuniorGroup, int nVeteranGroup);

		static int Current(COleDateTime t, int nYearValid, int nMonthStart, int nMonthStop);
		static int Current(int nYearValid, int nMonthStart, int nMonthStop);
		static int Current(int nYearValid, int nRegistrationTypeID, LPCTSTR szConnect);

		static int GetCurrentYear(int nRegistrationTypeID, LPCTSTR szConnect);


		static double GetSeconds(int iHours, int iMinutes, double dSeconds);
		static double GetSeconds(double dMinSec);

		static double GetMinSec(double dSeconds);

		static int GetHoursPart(double dSeconds);
		static int GetMinutesPart(double dSeconds);
		static double GetSecondsPart(double dSeconds);

		static int GetPercentile(int iPlace, int iParticipantCount);

		static double GetEventRateLongDistance(double dEventLength, double dNetPerfSEC);
		static double GetEventRateJumpThrow(double dEventLength, double dGrossPerfSEC);
		static double GetEventRateSprint(double dEventLength, double dGrossPerfSEC, double dGroupStartActual);

		static int GetPointDecrementValue(int iPoint, int iPointscale);

		static double GetNetPerformance(int iTimed,
										double dGroupStartActual,
										int iGrossPerformanceHOUR,
										int iGrossPerformanceMIN,
										double dGrossPerformanceSEC);
		// Static variables

		// Member variables

	private:

		// Member variables
};

#endif // !defined(AFX_CALCULATE_H__INCLUDED_)

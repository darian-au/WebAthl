#if !defined(AFX_RULESUBTYPE_H__INCLUDED_)
#define AFX_RULESUBTYPE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CRuleSubType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRuleSubType

class CRuleSubType : public CBitMaskEnum
{

	public:

		// Constructor
		CRuleSubType( );	

		// Destructor
		//~CRuleSubType( );

		// Member functions
		virtual CString GetName();
		virtual DWORD GetTypeCode();

		// Static functions
		static CString GetName(DWORD dwItem);
		static DWORD GetTypeCode(DWORD dwItem);

		// Member variables

		// Static variables
		static enum RuleSubTypeEnum  // bit mask
		{
			none									= 0x00000000,
			EligibilityEventsCompleted				= 0x00000001,
			PointscoreMaximumPoints					= 0x00000002,
			PointscoreMinimumPoints					= 0x00000004,
			PointscorePointscale					= 0x00000008,
			PointscoreEventsToCountForPoints		= 0x00000010,
			ConsistencyEventsToQualify				= 0x00000020,
			ConsistencyEventsBeforeAgegroupChange	= 0x00000040,
			RegroupEventsAbovePercentile			= 0x00000080,
			RegroupEventsBelowPercentile			= 0x00000100,
			ProcessingEligibleRegardlessOfDivision	= 0x00000200,
			ProcessingEligibleRegardlessOfGroup		= 0x00000400,
			ProcessingEligibleRegardlessOfFinancial	= 0x00000800,
			ProcessingSetOverallPlaceByDivision		= 0x00001000,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_RULESUBTYPE_H__INCLUDED_)

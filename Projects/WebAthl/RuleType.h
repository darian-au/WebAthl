#if !defined(AFX_RULETYPE_H__INCLUDED_)
#define AFX_RULETYPE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CRuleType.h : header file
//

#define	MAX_RULE_ELIGIBILITY	10
#define	MAX_RULE_POINTSCORE		4
#define	MAX_RULE_CONSISTENCY	2
#define	MAX_RULE_REGROUP		10
#define MAX_RULE_PROCESS		4

/////////////////////////////////////////////////////////////////////////////
// CRuleType

class CRuleType : public CBitMaskEnum
{

	public:

		// Constructor
		CRuleType( );	

		// Destructor
		//~CRuleType( );

		// Member functions
		virtual CString GetName();
		virtual int GetMax();

		// Static functions
		static CString GetName(DWORD dwItem);
		static int GetMax(DWORD dwItem);

		// Member variables

		// Static variables
		static enum RuleTypeEnum  // bit mask
		{
			none				= 0x00000000,
			Eligibility			= 0x00000001,
			Pointscore			= 0x00000002,
			Consistency			= 0x00000004,
			Regroup				= 0x00000008,
			Processing			= 0x00000010,
		};

	private:

		// Member variables

};

#endif // !defined(AFX_RULETYPE_H__INCLUDED_)

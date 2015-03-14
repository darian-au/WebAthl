#if !defined(AFX_CSWITCH_H__INCLUDED_)
#define AFX_CSWITCH_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CSwitch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSwitch

class CSwitch 
{
	public:

		// Constructor
		CSwitch(int *nArgc, char **szArgv, 
			bool bRemoveUsedSwitches = true,
			bool bFirstIndexIsZero = false,
			bool bCompareCase = true);

		// Destructor
		//~CSwitch();

		// Member functions
		const char *GetString(char *szName, const char *szDefault = NULL, int nArgs = 1);
		bool GetBoolean(char *szName);
		long GetLong(char *szName, long nDefault = 0);
		double GetDouble(char *szName, double dDefault = 0.0);

		// Static functions
		static int GetArgCount(char **szArgv);

	private:

		// Member variables
		int *m_nArgc;
		char **m_szArgv;

		bool m_bRemoveUsedSwitches;
		int m_bFirstIndex;
		bool m_bCompareCase;
};

#endif // !defined(AFX_CSWITCH_H__INCLUDED_)


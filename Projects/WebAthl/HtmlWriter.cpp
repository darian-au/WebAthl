// HtmlWriter.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "Registry.h"
#include "Properties.h"
#include "HttpServerVariable.h"
#include "CSV.h"
#include "StringStream.h"
#include "RecordsetEx.h"
#include "HttpServerProperties.h"

#include "HttpServerVariableEx.h"
#include "HtmlWriter.h"
#include "HtmlMonth.h"

#include "Convert.h"
#include "Util.h"
#include "Format.h"

#include "EventETypLocSet.h"
#include "SeriesSet.h"
#include "PersonSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlWriter

/////////////////////////////////////////////////////////////////////////////
// Constructor

CHtmlWriter::CHtmlWriter( CHttpServerContext* pCtxt , CHttpServer* pSrv )
	: CHttpServerVariableEx(pCtxt, pSrv)
{
//	CHttpServerProperties prop = CHttpServerProperties( this );
//	CHttpServerProperties* pProp = new CHttpServerProperties( this );

//	m_pProp = new CHttpServerProperties( this );
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CHtmlWriter::~CHtmlWriter( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions


void CHtmlWriter::StartForm(LPCTSTR szHeading, LPCTSTR szAction)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_STARTFORM);

	strOutput.Format(strForm,
		_T(szHeading),
		_T(szHeading),
//		_T(RemoveWhiteSpace(szHeading)),
		_T(GetAction(szAction)));

	*m_pCtxt << _T(strOutput);
	*m_pCtxt << _T(GetMFCIsapiCommand(szAction));
}

void CHtmlWriter::StartInLineForm(LPCTSTR szHeading, LPCTSTR szAction)
{
	CString strOutput;

	strOutput.Format("      <form name=\"%s\" method=\"POST\" action=\"%s\">\r\n",
		_T(szHeading),
//		_T(RemoveWhiteSpace(szHeading)),
		_T(GetAction(szAction)));

	*m_pCtxt << _T(strOutput);
	*m_pCtxt << _T(GetMFCIsapiCommand(szAction));
}


void CHtmlWriter::EndForm()
{
	*m_pCtxt << _T("\r\n");
	*m_pCtxt << _T("        </table></center></div>\r\n");
	*m_pCtxt << _T("      </form>\r\n");
}

void CHtmlWriter::EndInLineForm()
{
	*m_pCtxt << _T("\r\n");
	*m_pCtxt << _T("      </form>\r\n");
}

void CHtmlWriter::RadioButton(
				 LPCTSTR szTitle,
			     LPCTSTR szLabel,
			     LPCTSTR szVarName,
			     LPCTSTR szVarValue,
			     LPCTSTR szButtonData)
{
	CString strForm;
	CString strOutput;
	CString strChecked;

	CUtil::LoadLongResource(strForm, IDS_HTML_RADIOBUTTON);

	if (!_tcscmp(szVarValue, szButtonData))
	{
		strChecked = "checked";
	}

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		_T(szVarValue),
		_T(strChecked),
		_T(szLabel));

	*m_pCtxt << _T(strOutput);
}



void CHtmlWriter::TableHeader(LPCTSTR szTitle)
{
	CString strForm;
	CString strOutput;
	CString checked;

	CUtil::LoadLongResource(strForm, IDS_HTML_TABLEHEADER);

	strOutput.Format(strForm,
		_T(szTitle));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::RulesHeader(
				 LPCTSTR szLabel1,
				 LPCTSTR szLabel2,
				 LPCTSTR szLabel3,
				 LPCTSTR szLabel4,
				 LPCTSTR szLabel5,
				 LPCTSTR szLabel6)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_RULESHEADER);

	strOutput.Format(strForm,
		_T(szLabel1),
		_T(szLabel2),
		_T(szLabel3),
		_T(szLabel4),
		_T(szLabel5),
		_T(szLabel6));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::TableFooter()
{
	*m_pCtxt << _T("\r\n");
	*m_pCtxt << _T("        </table></center></div>\r\n");
}


void CHtmlWriter::RuleTypeSel(
				 LPCTSTR szHiddenName,
				 LPCTSTR szHiddenValue,
				 LPCTSTR szRuleID,
				 int nRuleID,
				 LPCTSTR szVarName,
				 int szVarValue,
				 LPCTSTR szLabel)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_RULETYPESEL);

	strOutput.Format(strForm,
		_T(szHiddenName),
		_T(szHiddenValue),
		_T(szRuleID),
		_T(nRuleID),
		_T(nRuleID),
		_T(szVarName),
		_T(szVarValue),
		_T(szLabel));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::RuleSubTypeSel(LPCTSTR szVarName)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_RULESUBTYPESEL);

	strOutput.Format(strForm,
		_T(szVarName));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::RuleSubmit(
			   LPCTSTR szVarName,
			   int     nVarValue,
			   LPCTSTR szVarNameS1,
			   LPCTSTR szVarNameS2)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_RULESUBMIT);

	strOutput.Format(strForm,
		_T(szVarName),
		_T(nVarValue),
		_T(szVarNameS1),
		_T(szVarNameS2));

	*m_pCtxt << _T(strOutput);
}



void CHtmlWriter::GroupsTable(
				 int    nGroupID,
				 double dGroupRate,
				 double dGroupStart)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_GROUPSTABLE);

	strOutput.Format(strForm,
		_T( nGroupID ),
		_T("GroupRateList"),
		_T( dGroupRate ),
		_T("GroupStartList"),
		_T( dGroupStart) );

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::GroupsTableHeader(
					   LPCTSTR szGroupID,
					   LPCTSTR szGroupRate,
					   LPCTSTR szGroupStart)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_GROUPSTABLEHEADER);

	strOutput.Format(strForm,
		_T(szGroupID),
		_T(szGroupRate),
		_T(szGroupStart));

	*m_pCtxt << _T(strOutput);
}


void CHtmlWriter::ResultsEntryTable(int nTimed,
									BOOL bPreEvent,
									int nDivision,
									int nPlace,
									int nPersonID,
									int nAgeGroup,
									int nPerfHOUR,
									int nPerfMIN,
									double dPerfSEC,
									int nGroupID,
									LPCTSTR szChestNo,
									int nPoints,
									int nNewGroupID,
									LPCTSTR szNewGroupMessage)
{
//	Timed = 1 -> Long Distance
//	Timed = 0 -> Jump or Throw
//	Timed = 2 -> Sprint

	CString strForm;
	CString strOutput;


	CString strRowStart          = _T("          <tr>\r\n");
	CString strRowItem           = _T("            <td align=\"%s\" nowrap><input type=\"text\" name=\"%s\" size=\"%s\" value=\"%s\" maxlength=\"%s\"></td>\r\n");
	CString strRowHidden         = _T("            <td align=\"%s\" nowrap><input type=\"hidden\" name=\"%s\" value=\"%s\"></td>\r\n");

	CString strRowLongDistance   = _T("            <td align=\"%s\" nowrap><input type=\"text\" name=\"%s\" size=\"2\" value=\"%s\" maxlength=\"2\"><strong>:</strong><input type=\"text\" name=\"%s\" size=\"2\" value=\"%s\" maxlength=\"2\"><strong>:</strong><input type=\"text\" name=\"%s\" size=\"6\" value=\"%s\" maxlength=\"6\"></td>\r\n");
	CString strRowSprint         = _T("            <td align=\"%s\" nowrap><input type=\"hidden\" name=\"%s\" value=\"%s\"><input type=\"text\" name=\"%s\" size=\"2\" value=\"%s\" maxlength=\"2\"><strong>:</strong><input type=\"text\" name=\"%s\" size=\"6\" value=\"%s\" maxlength=\"6\"></td>\r\n");
	CString strRowJumpThrow      = _T("            <td align=\"%s\" nowrap><input type=\"hidden\" name=\"%s\" value=\"%s\"><input type=\"hidden\" name=\"%s\" value=\"%s\"><input type=\"text\" name=\"%s\" size=\"10\" value=\"%s\" maxlength=\"6\"></td>\r\n");

	CString strRowEnd            = _T("          </tr>\r\n");


	strOutput += strRowStart;

	strForm.Format(strRowItem, _T("center"), _T("DivisionList"), _T("6"), _T(CConvert::itoa(nDivision)), _T("6") );
	strOutput += strForm;

	if( nPlace )
	{
		strForm.Format(strRowItem, _T("center"), _T("PlaceList"), _T("6"), _T(CConvert::itoa(nPlace)), _T("6") );
		strOutput += strForm;
	}
	else
	{
		strForm.Format(strRowHidden, _T("center"), _T("PlaceList"), _T(CConvert::itoa(nPlace)) );
		strOutput += strForm;
	}

	strForm.Format(strRowItem, _T("center"), _T("PersonIDList"), _T("10"), _T(CConvert::itoa(nPersonID)), _T("6") );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T("AgeGroupList"), _T("10"), _T(CConvert::itoa(nAgeGroup)), _T("6") );
	strOutput += strForm;

	switch(nTimed)
	{
		case 0 : // Jump or Throw
		{
			strForm.Format(strRowJumpThrow, _T("center"), _T("PerformanceHOURList"), _T(CConvert::itoa(nPerfHOUR)), _T( "PerformanceMINList" ), _T(CConvert::itoa(nPerfMIN)), _T( "PerformanceSECList" ), _T(CConvert::dtoa(dPerfSEC)) );
			strOutput += strForm;
			break;
		}
		case 1 : //Long Distance
		{
			strForm.Format(strRowLongDistance, _T("center"), _T("PerformanceHOURList"), _T(CConvert::itoa(nPerfHOUR)), _T( "PerformanceMINList" ), _T(CConvert::itoa(nPerfMIN)), _T( "PerformanceSECList" ), _T(CConvert::dtoa(dPerfSEC)) );
			strOutput += strForm;
			break;
		}
		case 2 : //	Sprint
		{
			strForm.Format(strRowSprint, _T("center"), _T("PerformanceHOURList"), _T(CConvert::itoa(nPerfHOUR)), _T( "PerformanceMINList" ), _T(CConvert::itoa(nPerfMIN)), _T( "PerformanceSECList" ), _T(CConvert::dtoa(dPerfSEC)) );
			strOutput += strForm;
			break;
		}
	}

	strForm.Format(strRowItem, _T("center"), _T("GroupIDList"), _T("10"), _T(CConvert::itoa(nGroupID)), _T("6") );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T("ChestNumberList"), _T("16"), _T(szChestNo), _T("60") );
	strOutput += strForm;

	if( bPreEvent )
	{
		strForm.Format(strRowHidden, _T("center"), _T("PointsList"), _T(CConvert::itoa(nPoints)) );
		strOutput += strForm;

		strForm.Format(strRowHidden, _T("center"), _T("NewGroupIDList"), _T(CConvert::itoa(nNewGroupID)) );
		strOutput += strForm;

		strForm.Format(strRowHidden, _T("center"), _T("NewGroupMessageList"), _T(szNewGroupMessage) );
		strOutput += strForm;
	}
	else
	{
		strForm.Format(strRowItem, _T("center"), _T("PointsList"), _T("6"), _T(CConvert::itoa(nPoints)), _T("6") );
		strOutput += strForm;

		strForm.Format(strRowItem, _T("center"), _T("NewGroupIDList"), _T("6"), _T(CConvert::itoa(nNewGroupID)), _T("6") );
		strOutput += strForm;

		strForm.Format(strRowItem, _T("center"), _T("NewGroupMessageList"), _T("16"), _T(szNewGroupMessage), _T("60") );
		strOutput += strForm;
	}

	strOutput += strRowEnd;


	*m_pCtxt << _T(strOutput);
}



void CHtmlWriter::ResultsEntryTableHeader(
						BOOL bPreEvent,
					    LPCTSTR szDivision,
					    LPCTSTR szPlace,
					    LPCTSTR szPerson,
					    LPCTSTR szAgeGroup,
					    LPCTSTR szPerformance,
					    LPCTSTR szGroup,
					    LPCTSTR szChestNumber,
					    LPCTSTR szPoints,
					    LPCTSTR szNewGroup,
					    LPCTSTR szNewGroupMessage)
{
	CString strForm;
	CString strOutput;

	CString strRowStart          = _T("          <tr>\r\n");
	CString strRowItem           = _T("            <td align=\"%s\" nowrap>%s</td>\r\n");
	CString strRowEnd            = _T("          </tr>\r\n");


	strOutput += strRowStart;

	strForm.Format(strRowItem, _T("center"), _T(szDivision) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szPlace) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szPerson) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szAgeGroup) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szPerformance) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szGroup) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szChestNumber) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szPoints) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szNewGroup) );
	strOutput += strForm;

	strForm.Format(strRowItem, _T("center"), _T(szNewGroupMessage) );
	strOutput += strForm;

	strOutput += strRowEnd;


	*m_pCtxt << _T(strOutput);
}



void CHtmlWriter::StandardTimeTable(
					   LPCTSTR szAgeGroup,
					   int   nVarValuepHOUR,
					   int   nVarValuepMIN,
					   double dVarValuepSEC,
					   int   nVarFactName,
					   double dVarFactValue)
{
	CString strForm;
	CString strOutput;
	CString strFact;
	int nColspan = 3;

	if(nVarFactName)
	{
		nColspan = 2;
		strFact.Format("<td colspan=\"2\" nowrap><input type=\"text\" name=\"FactorList\" size=\"10\" value=\"%s\" maxlength=\"10\"></td>", CConvert::dtoa(dVarFactValue,4));
	}
	else
	{
		strFact.Format("<input type=\"hidden\" name=\"FactorList\" value=\"%s\">", CConvert::dtoa(dVarFactValue,4));
	}

	CUtil::LoadLongResource(strForm, IDS_HTML_STANDARDTIMETABLE);

	strOutput.Format(strForm,
		_T(CConvert::itoa(nColspan)),
		_T(szAgeGroup),
		_T(CConvert::itoa(nColspan)),
		_T("PerformanceHOURList"),
		_T(CConvert::itoa(nVarValuepHOUR)),
		_T("PerformanceMINList"),
		_T(CConvert::itoa(nVarValuepMIN)),
		_T("PerformanceSECList"),
		_T(CConvert::dtoa(dVarValuepSEC)),
		_T(strFact));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::StandardDistTable(
					   LPCTSTR szAgeGroup,
					   double dVarValuepSEC,
					   int   nVarFactName,
					   double dVarFactValue)
{
	CString strForm;
	CString strOutput;
	CString strFact;
	int nColspan = 3;

	if(nVarFactName)
	{
		nColspan = 2;
		strFact.Format("<td colspan=\"2\" nowrap><input type=\"text\" name=\"FactorList\" size=\"10\" value=\"%s\" maxlength=\"10\"></td>", CConvert::dtoa(dVarFactValue,4));
	}
	else
	{
		strFact.Format("<input type=\"hidden\" name=\"FactorList\" value=\"%s\">", CConvert::dtoa(dVarFactValue,4));
	}

	CUtil::LoadLongResource(strForm, IDS_HTML_STANDARDDISTTABLE);

	strOutput.Format(strForm,
		_T("PerformanceHOURList"),
		_T(CConvert::itoa(0)),
		_T("PerformanceMINList"),
		_T(CConvert::itoa(0)),
		_T(CConvert::itoa(nColspan)),
		_T(szAgeGroup),
		_T(CConvert::itoa(nColspan)),
		_T("PerformanceSECList"),
		_T(CConvert::dtoa(dVarValuepSEC)),
		_T(strFact));

	*m_pCtxt << _T(strOutput);
}



void CHtmlWriter::StandardTableHeader(
					    LPCTSTR szAgeGroup,
					    LPCTSTR szRecCategory,
					    LPCTSTR szFactor)
{
	CString strForm;
	CString strOutput;
	CString strFact;
	int nColspan = 3;

	if( _tcscmp(szFactor,"") )
	{
		nColspan = 2;
		strFact.Format("<td colspan=\"2\" align=\"center\" nowrap>%s</td>", szFactor);
	}

	CUtil::LoadLongResource(strForm, IDS_HTML_STANDARDTABLEHEADER);

	strOutput.Format(strForm,
		nColspan,
		_T(szAgeGroup),
		nColspan,
		_T(szRecCategory),
		_T(strFact));

	*m_pCtxt << _T(strOutput);
}



void CHtmlWriter::RosterTable(
				 LPCTSTR szLabel1,
				 LPCTSTR szLabel2)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_ROSTERTABLE);

	strOutput.Format(strForm,
		_T(szLabel1),
		_T(szLabel2));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::StartRoster(
				 LPCTSTR szVarName)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_STARTROSTER);

	strOutput.Format(strForm,
		_T(szVarName));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::EndRoster(
			   LPCTSTR szLabel)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_ENDROSTER);

	strOutput.Format(strForm,
		_T(szLabel));

	*m_pCtxt << _T(strOutput);
}


void CHtmlWriter::StartSelectBox(
					LPCTSTR szTitle,
					LPCTSTR szVarName)
{
	StartListBox(szTitle, szVarName, 1, FALSE);
}

void CHtmlWriter::StartListBox(
					LPCTSTR szTitle,
					LPCTSTR szVarName,
					int nHeight,
					BOOL bMultiple)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_STARTSELECTBOX);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		nHeight,
		(bMultiple ? _T("multiple") : _T("")) );

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::AddSelectBox(
  				  LPCTSTR szLabel,
				  LPCTSTR szVarValue,
				  LPCTSTR szButtonData)
{
	CString strForm;
	CString strOutput;
	CString strSelected;

	CUtil::LoadLongResource(strForm, IDS_HTML_ADDSELECTBOX);

	if (!_tcscmp(szVarValue, szButtonData))
		strSelected = "selected";

	strOutput.Format(strForm,
		_T(strSelected),
		_T(szVarValue),
		_T(szLabel));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::EndSelectBox()
{
	CString strOutput;

	CUtil::LoadLongResource(strOutput, IDS_HTML_ENDSELECTBOX);

	*m_pCtxt << _T(strOutput);
}


void CHtmlWriter::CheckBox(
			  LPCTSTR szTitle,
			  LPCTSTR szLabel,
			  LPCTSTR szVarName,
			  LPCTSTR szVarValue,
			  LPCTSTR szButtonData)
{
	CString strForm;
	CString strOutput;
	CString strChecked;

	CUtil::LoadLongResource(strForm, IDS_HTML_CHECKBOX);

	if (!_tcscmp(szVarValue, szButtonData))
		strChecked = "checked";

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		_T(szVarValue),
		_T(strChecked),
		_T(szLabel));

	*m_pCtxt << _T(strOutput);
}


void CHtmlWriter::TimeBox(
			 LPCTSTR szTitle,
			 LPCTSTR szVarName,
			 int   nVarValueHOUR,
			 int   nVarValueMIN,
			 double dVarValueSEC)
{
	CString strForm;
	CString strOutput;
	CString strChecked;

	CUtil::LoadLongResource(strForm, IDS_HTML_TIMEBOX);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		_T(CConvert::itoa(nVarValueHOUR)),
		_T(szVarName),
		_T(CConvert::itoa(nVarValueMIN)),
		_T(szVarName),
		_T(CConvert::dtoa(dVarValueSEC)));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::MonthBox(
			  LPCTSTR szTitle,
			  LPCTSTR szVarName,
			  int   nVarValueMONTH)
{
	CString strForm;
	CString strOutput;
	CString strChecked;
	CHtmlMonth month = CHtmlMonth(nVarValueMONTH);

	CUtil::LoadLongResource(strForm, IDS_HTML_MONTHBOX);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		_T( month.m_strJan ),	
		_T( month.m_strFeb ),	
		_T( month.m_strMar ),	
		_T( month.m_strApr ),	
		_T( month.m_strMay ),	
		_T( month.m_strJun ),	
		_T( month.m_strJul ),	
		_T( month.m_strAug ),	
		_T( month.m_strSep ),	
		_T( month.m_strOct ),	
		_T( month.m_strNov ),	
		_T( month.m_strDec ));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::DateBox(LPCTSTR szTitle, LPCTSTR szVarName, long lDaysFromToday)
{
	COleDateTime today = COleDateTime::GetCurrentTime();

	COleDateTimeSpan span = COleDateTimeSpan( labs(lDaysFromToday), 0, 0, 0 );

	if( lDaysFromToday < 0 )
		today -= span;
	else
		today += span;

	DateBox( szTitle, szVarName, 
		today.GetDay(), today.GetMonth(), today.GetYear() );
}

void CHtmlWriter::DateBox(LPCTSTR szTitle, LPCTSTR szVarName)
{
	COleDateTime today = COleDateTime::GetCurrentTime();

	DateBox( szTitle, szVarName, 
		today.GetDay(), today.GetMonth(), today.GetYear() );
}

void CHtmlWriter::DateBox(
			 LPCTSTR szTitle,
			 LPCTSTR szVarName,
			 int   nVarValueDAY,
			 int   nVarValueMONTH,
			 int   nVarValueYEAR)
{
	CString strForm;
	CString strOutput;
	CHtmlMonth month = CHtmlMonth(nVarValueMONTH);

	CString strValueDAY;
	CString strValueYEAR;

	if( (!CRecordsetEx::IsItemNull(nVarValueDAY)) && (nVarValueDAY != 0) ) 
		strValueDAY.Format("%s", CConvert::itoa(nVarValueDAY));

	if( (!CRecordsetEx::IsItemNull(nVarValueYEAR)) && (nVarValueYEAR != 0) ) 
		strValueYEAR.Format("%s", CConvert::itoa(nVarValueYEAR));

	CUtil::LoadLongResource(strForm, IDS_HTML_DATEBOX);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		_T(strValueDAY),
		_T(szVarName),
		_T( month.m_strJan ),	
		_T( month.m_strFeb ),	
		_T( month.m_strMar ),	
		_T( month.m_strApr ),	
		_T( month.m_strMay ),	
		_T( month.m_strJun ),	
		_T( month.m_strJul ),	
		_T( month.m_strAug ),	
		_T( month.m_strSep ),	
		_T( month.m_strOct ),	
		_T( month.m_strNov ),	
		_T( month.m_strDec ),
		_T(szVarName),
		_T(strValueYEAR));

	*m_pCtxt << _T(strOutput);
}


void CHtmlWriter::NonEditDateBox(
					LPCTSTR szTitle,
					int   nVarValueDAY,
					int   nVarValueMONTH,
					int   nVarValueYEAR)
{
	NonEditText(szTitle, CFormat::FormatDate(nVarValueDAY, nVarValueMONTH, nVarValueYEAR) );
}

void CHtmlWriter::SubmitButton(LPCTSTR szVarValue, int nColspan)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_SUBMITBUTTON);

	strOutput.Format(strForm,
		(nColspan / 2),
		((nColspan / 2) + (nColspan % 2)),
		_T(szVarValue));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::ResetButton(int nColspan)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_RESETBUTTON);

	strOutput.Format(strForm,
		(nColspan / 2),
		((nColspan / 2) + (nColspan % 2)) );

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::HiddenText(
				LPCTSTR szVarName,
				LPCTSTR szVarValue)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_HIDDENTEXT);

	strOutput.Format(strForm,
		_T(szVarName),
		_T(szVarValue));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::HiddenInt(
			   LPCTSTR szVarName,
			   int   nVarValue)
{
	HiddenText(szVarName, CConvert::itoa(nVarValue));
}

void CHtmlWriter::HiddenFloat(
				 LPCTSTR szVarName,
				 double dVarValue)
{
	HiddenText(szVarName, CConvert::dtoa(dVarValue));
}

void CHtmlWriter::PasswordBox(
				 LPCTSTR szTitle,
				 LPCTSTR szVarName,
				 LPCTSTR szVarValue)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_PASSWORDBOX);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		_T(szVarValue));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::EditTextBox(
				 LPCTSTR szTitle,
				 LPCTSTR szVarName,
				 LPCTSTR szVarValue, 
				 int nSize)
{
	CString strForm;
	CString strOutput;

	CString strMaxLength;

	if(nSize < 20)
		strMaxLength.Format(" maxlength=\"%d\"", nSize);

	strForm += _T("          <tr>\r\n");
	strForm += _T("            <td colspan=\"3\" align=\"right\" nowrap>%s</td>\r\n");
	strForm += _T("            <td colspan=\"3\" nowrap><input type=\"text\" name=\"%s\" size=\"%d\" value=\"%s\"%s></td>\r\n");
	strForm += _T("          </tr>\r\n");

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		nSize,
		_T(szVarValue),
		_T(strMaxLength));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::EditTextBoxLarge(
					  LPCTSTR szTitle,
					  LPCTSTR szVarName,
					  LPCTSTR szVarValue)
{
	EditTextBox(szTitle, szVarName, szVarValue, 30);
}


void CHtmlWriter::EditTextBoxSmall(
					  LPCTSTR szTitle,
					  LPCTSTR szVarName,
					  LPCTSTR szVarValue)
{
	EditTextBox(szTitle, szVarName, szVarValue, 16);
}

void CHtmlWriter::EditIntBox(
				LPCTSTR szTitle,
				LPCTSTR szVarName,
				int   nVarValue)
{
	CString strValue;
	if( !CRecordsetEx::IsItemNull(nVarValue) ) 
		strValue = CConvert::itoa(nVarValue);

	EditTextBox(szTitle, szVarName, strValue, 6);
}

void CHtmlWriter::EditFloatBox(
				  LPCTSTR szTitle,
				  LPCTSTR szVarName,
				  double dVarValue)
{
	CString strValue;
	if( !CRecordsetEx::IsItemNull(dVarValue) ) 
		strValue = CConvert::dtoa(dVarValue);

	EditTextBox(szTitle, szVarName, strValue, 10);
}

void CHtmlWriter::NonEditText(
				 LPCTSTR szTitle,
				 LPCTSTR szVarValue)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_NONEDITTEXT);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarValue));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::NonEditInt(
				LPCTSTR szTitle,
				int   nVarValue)
{
	NonEditText(szTitle, CConvert::itoa(nVarValue));
}

void CHtmlWriter::NonEditFloat(
				  LPCTSTR szTitle,
				  double dVarValue)
{
	NonEditText(szTitle, CConvert::dtoa(dVarValue));
}


void CHtmlWriter::WritePageTitle(LPCTSTR szAddOn)
{
	CString strTitle;

	CHttpServerProperties prop = CHttpServerProperties( this );

	strTitle.LoadString(IDS_PAGE_TITLE);

	if( _tcsclen(szAddOn) > 0 )
	{
		strTitle += ": ";
		strTitle += szAddOn;
	}

	CString strStyleSheet = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::StyleSheet);

	CString strStyleSheetLink;
	
	if( !prop.IsEmpty(strStyleSheet) && !strStyleSheet.IsEmpty() )
	{
		strStyleSheetLink.Format("<link href=\"%s\" rel=\"stylesheet\" type=\"text/css\">\r\n", strStyleSheet);
	}

	*m_pCtxt << "<html>\r\n";
	*m_pCtxt << "<head>\r\n";
	*m_pCtxt << "<title>";
	*m_pCtxt << _T(strTitle);
	*m_pCtxt << "</title>\r\n";
	*m_pCtxt << _T(strStyleSheetLink);
	*m_pCtxt << "</head>\r\n";
}

void CHtmlWriter::WritePageMenu(LPCTSTR szMenu, LPCTSTR szHeading)
{
	CHttpServerProperties prop = CHttpServerProperties( this );

	CString strLogo = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Logo);
	CString strMenuImage = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::MenuImage);
	CString strMenuColor = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::MenuColor);
	CString strBackgroundImage = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::BackgroundImage);
	CString strBackgroundColor = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::BackgroundColor);
	CString strFont = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Font);

	bool bLogo = ( !prop.IsEmpty(strLogo) && !strLogo.IsEmpty() );
	bool bMenuImage = ( !prop.IsEmpty(strMenuImage) && !strMenuImage.IsEmpty() );
	bool bMenuColor = ( !prop.IsEmpty(strMenuColor) && !strMenuColor.IsEmpty() );
	bool bBackgroundImage = ( !prop.IsEmpty(strBackgroundImage) && !strBackgroundImage.IsEmpty() );
	bool bBackgroundColor = ( !prop.IsEmpty(strBackgroundColor) && !strBackgroundColor.IsEmpty() );
	bool bFont = ( !prop.IsEmpty(strFont) && !strFont.IsEmpty() );


	*m_pCtxt << _T("<body");
	if( bBackgroundImage )
	{
		*m_pCtxt << _T(" background=\"");
		*m_pCtxt << _T(strBackgroundImage);
		*m_pCtxt << _T("\"");
	}
	if( bBackgroundColor )
	{
		*m_pCtxt << _T(" bgcolor=\"");
		*m_pCtxt << _T(strBackgroundColor);
		*m_pCtxt << _T("\"");
	}
	if( bFont )
	{
		*m_pCtxt << _T(" style=\"{ font-family: '");
		*m_pCtxt << _T(strFont);
		*m_pCtxt << _T("' ; }\"");
	}
	*m_pCtxt << _T(">\r\n");

	if( bFont )
	{
		*m_pCtxt << _T("<basefont face=\"");
		*m_pCtxt << _T(strFont);
		*m_pCtxt << _T("\">\r\n");
	}

	*m_pCtxt << _T("<table border=\"0\" width=\"100%\" height=\"100%\" cellspacing=\"0\" cellpadding=\"10\">\r\n");
	*m_pCtxt << _T("  <tr>\r\n");

	*m_pCtxt << _T("    <td align=\"center\" class=\"MenuBar\"");
	if( bMenuImage )
	{
		*m_pCtxt << _T(" background=\"");
		*m_pCtxt << _T(strMenuImage);
		*m_pCtxt << _T("\"");
	}
	if( bMenuColor )
	{
		*m_pCtxt << _T(" bgcolor=\"");
		*m_pCtxt << _T(strMenuColor);
		*m_pCtxt << _T("\"");
	}
	*m_pCtxt << _T("><font size=\"1\">");
	*m_pCtxt << _T(szMenu);
	*m_pCtxt << _T("</font></td>\r\n");

	*m_pCtxt << _T("    <td align=\"center\" width=\"100%\"><h1>");
	*m_pCtxt << _T(szHeading);
	*m_pCtxt << _T("</h1></td>\r\n");

	if( bLogo )
	{
		*m_pCtxt << _T("    <td align=\"right\"><img src=\"");
		*m_pCtxt << _T(strLogo);
		*m_pCtxt << _T("\"></td>\r\n");
	}

	*m_pCtxt << _T("  </tr>\r\n\r\n");


	*m_pCtxt << _T("  <tr>\r\n");
	*m_pCtxt << _T("    <td class=\"MenuBar\"");
	if( bMenuImage )
	{
		*m_pCtxt << _T(" background=\"");
		*m_pCtxt << _T(strMenuImage);
		*m_pCtxt << _T("\"");
	}
	if( bMenuColor )
	{
		*m_pCtxt << _T(" bgcolor=\"");
		*m_pCtxt << _T(strMenuColor);
		*m_pCtxt << _T("\"");
	}
	*m_pCtxt << _T("><hr class=\"MenuSpacer\" width=\"160\" size=\"0\"");
	if( bMenuColor )
	{
		*m_pCtxt << _T(" color=\"");
		*m_pCtxt << _T(strMenuColor);
		*m_pCtxt << _T("\"");
	}
	*m_pCtxt << _T(" noshade></td>\r\n");

	if( bLogo )
	{
		*m_pCtxt << _T("    <td align=\"center\" colspan=\"2\">");
	}
	else
	{
		*m_pCtxt << _T("    <td align=\"center\">");
	}
	if( !prop.IsLicensed() )
	{
		*m_pCtxt << _T("<b><font color=\"#FF0000\" size=\"1\">Unregistered</font></b>");
	}
	*m_pCtxt << _T("</td>\r\n");

	*m_pCtxt << _T("  </tr>\r\n\r\n");

	*m_pCtxt << _T("  <tr>\r\n");
	*m_pCtxt << _T("    <td class=\"MenuBar\" align=\"left\" width=\"160\" height=\"100%\" valign=\"top\"");
	if( bMenuImage )
	{
		*m_pCtxt << _T(" background=\"");
		*m_pCtxt << _T(strMenuImage);
		*m_pCtxt << _T("\"");
	}
	if( bMenuColor )
	{
		*m_pCtxt << _T(" bgcolor=\"");
		*m_pCtxt << _T(strMenuColor);
		*m_pCtxt << _T("\"");
	}
	*m_pCtxt << _T(">\r\n");

}
/*
void CHtmlWriter::WritePageMenu(
				   LPCTSTR szMenu,
				   LPCTSTR szHeading)
{
	CString strOutput;
	CString strMenuBar;

	CString strLogo;
	CString strMenu = _T(" class=\"MenuBar\" ");
	CString strBG;
	CString strFont;
	CString strStyle;

	CString strMenuSpacer;

	CHttpServerProperties prop = CHttpServerProperties( this );

	CString strPropLogo = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Logo);

	CString strPropMenuImage =  prop.GetEx(CHtmlKey::Appearance,CHtmlKey::MenuImage);
	CString strPropMenuColor =  prop.GetEx(CHtmlKey::Appearance,CHtmlKey::MenuColor);

	CString strPropBackgroundImage =  prop.GetEx(CHtmlKey::Appearance,CHtmlKey::BackgroundImage);
	CString strPropBackgroundColor =  prop.GetEx(CHtmlKey::Appearance,CHtmlKey::BackgroundColor);

	CString strPropFont =  prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Font);

	CString strLicensed;

	if( !prop.IsLicensed() )
	{
		strLicensed = _T("<b><font color=\"#FF0000\" size=\"1\">Unregistered</font></b>");
	}

	if( _tcscmp(strPropLogo, "") )
	{
		strLogo.Format("<td align=\"right\"><img src=\"%s\"></td>", strPropLogo);
	}

	if( _tcscmp(strPropMenuImage, "") )
	{
		strMenu += _T(" background=\"" );
		strMenu += _T(strPropMenuImage);
		strMenu += _T("\"");
	}
	if( _tcscmp(strPropMenuColor, "") )
	{
		strMenu += _T(" bgcolor=\"" );
		strMenu += _T(strPropMenuColor);
		strMenu += _T("\"");

		strMenuSpacer += _T(" color=\"");
		strMenuSpacer += _T(strPropMenuColor);
		strMenuSpacer += _T("\"");
	}

	if( _tcscmp(strPropBackgroundImage, "") )
	{
		strBG += _T(" background=\"" );
		strBG += _T(strPropBackgroundImage);
		strBG += _T("\"");
	}
	if( _tcscmp(strPropBackgroundColor, "") )
	{
		strBG += _T(" bgcolor=\"" );
		strBG += _T(strPropBackgroundColor);
		strBG += _T("\"");
	}

	if( _tcscmp(strPropFont, "") )
	{
		strFont.Format("<basefont face=\"%s\">", strPropFont);
		strStyle.Format(" style=\"font-family: %s\"", strPropFont);
	}

	CUtil::LoadLongResource(strMenuBar, IDS_HTML_MENUBAR);
	strOutput.Format(strMenuBar,
		_T(strBG),
		_T(strStyle),

		_T(strFont),

		_T(strMenu),

		_T(szMenu),
		_T(szHeading),
		_T(strLogo),

		_T(strMenu),

		_T(strMenuSpacer),
		_T(strLicensed),

		_T(strMenu));

	*m_pCtxt << _T(strOutput);
}
*/
void CHtmlWriter::WritePageMenuItem(
					   LPCTSTR szAction,
					   LPCTSTR szName,
					   int nInitNum,
					   ...)
{
	CString strOutput;
	CString strHidden;
	CString strAction = GetAction(szAction);
	CString strMenuItem;

	CHttpServerProperties prop = CHttpServerProperties( this );

	CString strExitURL = prop.GetEx(CHtmlKey::Navigation,CHtmlKey::ExitURL);

	CString strFormMethod;
	CString strSubmitName;
	CString strIsapiCommand;

	va_list marker;
	char    *szInit;
	int		nInitCounter = 0;

	if( !strExitURL.Compare( szAction ) ) 
	{
		strAction = _T( szAction );
		strFormMethod.Format("%s", "GET");
		strSubmitName.Format("%s", "");
	}
	else
	{
		strFormMethod.Format("%s", "POST");
		strSubmitName.Format("%s", "name=\"Submit\"");

		strIsapiCommand = _T( GetMFCIsapiCommand(szAction) );
	}

	strMenuItem += _T("      <form method=\"%s\" action=\"%s\">\r\n");
	strMenuItem += _T( strIsapiCommand );
	strMenuItem += _T("      <table><tr>\r\n");
	strMenuItem += _T("        <td valign=\"top\"><input class=\"MenuButton\" type=\"submit\" value=\"  ->  \" %s></td>\r\n");
	strMenuItem += _T("        <td><small>%s</small></td>\r\n");

	va_start( marker, nInitNum );				// Initialize variable arguments.	//

	for( nInitCounter = 0 ; nInitCounter < nInitNum ; nInitCounter++ )	// Get next variable argument.		//
	{
		szInit = va_arg( marker, char* );

		if ( _tcslen(szInit) > 0 )
		{
			if(nInitCounter > 0)
			{
				strHidden.Format("        <input type=\"hidden\" name=\"Init%i\" value=\"%s\">\r\n", nInitCounter, szInit);
			}
			else
			{
				strHidden.Format("        <input type=\"hidden\" name=\"Init\" value=\"%s\">\r\n", szInit);
			}
	
			strMenuItem += strHidden;
		}
	}

	va_end( marker );						// Reset variable arguments.		//


	strMenuItem += _T("      </tr></table>\r\n");
	strMenuItem += _T("      </form>\r\n");


	strOutput.Format(strMenuItem, strFormMethod, strAction, strSubmitName, szName);

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::EndMenu()
{
	CHttpServerProperties prop = CHttpServerProperties( this );

	CString strLogo = prop.GetEx(CHtmlKey::Appearance,CHtmlKey::Logo);
	bool bLogo = ( !prop.IsEmpty(strLogo) && !strLogo.IsEmpty() );

	*m_pCtxt << _T("    </td>\r\n\r\n");

	if( bLogo )
	{
		*m_pCtxt << _T("    <td valign=\"top\" align=\"left\" colspan=\"2\">\r\n");
	}
	else
	{
		*m_pCtxt << _T("    <td valign=\"top\" align=\"left\">\r\n");
	}
}

void CHtmlWriter::EndPage()
{
	*m_pCtxt << _T("\r\n");
	*m_pCtxt << _T("    </td>\r\n");
	*m_pCtxt << _T("  </tr>\r\n");
	*m_pCtxt << _T("</table>\r\n");
}



void CHtmlWriter::HtmlTable(CStringArray* strColumn)
{
	HtmlTable(strColumn, -1);
}

void CHtmlWriter::HtmlTable(CStringArray* strColumn, int nAlign)
{
	CString strForm;
	CString strOutput;

	CString strAlign = _T(" align=");

	switch( nAlign )
	{
		case -1 :
			strAlign += _T("\"left\" ");
			break;
		case 0 :
			strAlign += _T("\"center\" ");
			break;
		case 1 :
			strAlign += _T("\"right\" ");
			break;
	}

	strOutput = ("          <tr>\r\n");

	int nCols = strColumn->GetSize( );

	for(int i = 0; i < nCols ; i++ )
	{
		strForm.Format("            <td %s nowrap>%s</td>\r\n", strAlign, strColumn->GetAt(i));
		strOutput += strForm;
	}

	strOutput += _T("          </tr>\r\n");

	*m_pCtxt << _T(strOutput);
}


void CHtmlWriter::HorizontalRule(int nColspan)
{
	CString strForm;
	CString strOutput;
	CString checked;

	CUtil::LoadLongResource(strForm, IDS_HTML_HORIZONTALRULE);

	strOutput.Format(strForm, nColspan);

	*m_pCtxt << _T(strOutput);
}


void CHtmlWriter::EmptyHorizontalRule(int nColspan)
{
	CString strForm;
	CString strOutput;
	CString checked;

	CUtil::LoadLongResource(strForm, IDS_HTML_EMPTYHORIZONTALRULE);

	strOutput.Format(strForm, nColspan);

	*m_pCtxt << _T(strOutput);
}


void CHtmlWriter::HeadingHRule(
				  int nColspan,
				  LPCTSTR szTitle)
{
	CString strForm;
	CString strOutput;

	strForm += _T( "          <tr>\r\n" );
	strForm += _T( "            <td nowrap colspan=\"%d\"><h2 align=\"center\">%s</h2></td>\r\n" );
	strForm += _T( "          </tr>\r\n" );

	strOutput.Format(strForm, nColspan, szTitle);

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::TextArea(
			  LPCTSTR szTitle,
			  LPCTSTR szVarName,
			  int nRows,
			  int nCols,
			  LPCTSTR szVarValue)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_TEXTAREA);

	strOutput.Format(strForm,
		_T(szTitle),
		nRows,
		_T(szVarName),
		nCols,
		_T(szVarValue));

	*m_pCtxt << _T(strOutput);
}



void CHtmlWriter::HRuleAlign(
				int nCols,
				int nColspan,
				BOOL bLeftalign)
{
	CString strHRule;
	CString strOutput;

	int i;

	*m_pCtxt << _T("          <tr>\r\n");

	if(bLeftalign)
	{
		strHRule.Format("            <td colspan=\"%d\" nowrap><hr></td>\r\n", nColspan);
		*m_pCtxt << _T(strHRule);
		for( i = 0 ; i < (nCols - nColspan) ; i++ )
		{
			*m_pCtxt << _T("            <td></td>\r\n");
		}
	}
	else
	{
		for( i = 0 ; i < (nCols - nColspan) ; i++ )
		{
			*m_pCtxt << _T("            <td></td>\r\n");
		}
		strHRule.Format("            <td colspan=\"%d\" nowrap><hr></td>\r\n", nColspan);
		*m_pCtxt << _T(strHRule);
	}
	*m_pCtxt << _T("          </tr>\r\n");
}

void CHtmlWriter::MultiFormHeader(
					 LPCTSTR szTitle,
					 LPCTSTR szComment)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_MULTIFORMHEADER);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szComment));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::MultiFormCheckBox(
					   LPCTSTR szTitle,
					   LPCTSTR szLabel,
					   LPCTSTR szVarName,
					   LPCTSTR szVarValue,
					   LPCTSTR szButtonData,
					   LPCTSTR szComment)
{
	CString strForm;
	CString strOutput;
	CString strChecked;

	CUtil::LoadLongResource(strForm, IDS_HTML_MULTIFORMCHECKBOX);

	if (!_tcscmp(szVarValue, szButtonData))
		strChecked = "checked";

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		_T(szVarValue),
		_T(strChecked),
		_T(szLabel),
		_T(szComment));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::MultiFormRadioButton(
						  LPCTSTR szTitle,
						  LPCTSTR szLabel,
						  LPCTSTR szVarName,
						  LPCTSTR szVarValue,
						  LPCTSTR szButtonData)
{
	CString strForm;
	CString strOutput;
	CString strChecked;

	CUtil::LoadLongResource(strForm, IDS_HTML_MULTIFORMRADIOBUTTON);

	if (!_tcscmp(szVarValue, szButtonData))
		strChecked = "checked";

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szVarName),
		_T(szVarValue),
		_T(strChecked),
		_T(szLabel));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::MultiFormStartSelectBox(
							 LPCTSTR szTitle,
							 LPCTSTR szLabel,
							 LPCTSTR szVarName)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_MULTIFORMSTARTSELECTBOX);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szLabel),
		_T(szVarName));

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::MultiFormEditIntBox(
						 LPCTSTR szTitle,
						 LPCTSTR szLabel,
						 LPCTSTR szVarName,
						 int   nVarValue)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_MULTIFORMEDITINTBOX);

	strOutput.Format(strForm,
		_T(szTitle),
		_T(szLabel),
		_T(szVarName),
		nVarValue);

	*m_pCtxt << _T(strOutput);
}

void CHtmlWriter::MultiFormComment(
					  LPCTSTR szComment)
{
	CString strForm;
	CString strOutput;

	CUtil::LoadLongResource(strForm, IDS_HTML_MULTIFORMCOMMENT);

	strOutput.Format(strForm,
		_T(szComment));

	*m_pCtxt << _T(strOutput);
}


CString CHtmlWriter::InLineInput(
					LPCTSTR szType,
					LPCTSTR szVarName,
					LPCTSTR szVarValue,
					int		nSize,
					LPCTSTR szButtonData)
{
	CString strOutput;

	CString strType;
	CString strName;
	CString strValue;
	CString strSize;
	CString strChecked;

	if(szButtonData != NULL)
	{
		if (!_tcscmp(szVarValue, szButtonData))	
			strChecked = _T("checked");
	}

	if( szType != NULL )		
		strType.Format ("Type=\"%s\"", szType);

	if( szVarName != NULL )	
		strName.Format ("Name=\"%s\"", szVarName);

	if( szVarValue != NULL )	
		strValue.Format("Value=\"%s\"", szVarValue);

	if( nSize )		
		strSize.Format ("Size=\"%d\"", nSize);

	strOutput.Format(_T("<INPUT %s %s %s %s %s>"),
		_T(strType),
		_T(strName),
		_T(strValue),
		_T(strSize),
		_T(strChecked));

//	*m_pCtxt << _T(strOutput);

	return strOutput;
}




int CHtmlWriter::SelectEventBox( 
				   LPCTSTR szTitle, 
				   LPCTSTR szVarName,
				   CRecordset* rs,
				   int iSelectedEventID,
				   LPCTSTR szIncludeNone)
// If iSelectedEventID < 0 :
// Assume that EventNo order by Descending, and
// that EventNo is in Date Order. Then pick the first event
// that has a date less than or equal to todays date.
{
		int iEvents = 0;
		int iEventID;

		bool bSelectedEventFound = false;

		COleDateTime today = COleDateTime::GetCurrentTime();
		COleDateTime eventday;

		try
		{
			CEventETypLocSet* rsEvent = (CEventETypLocSet*)(rs);

			CString strEvent;

			if( !rsEvent->IsEOF( ) )
			{
				StartSelectBox(szTitle, szVarName);
				if( szIncludeNone != NULL )
					AddSelectBox(szIncludeNone, "0", CConvert::itoa(iSelectedEventID));

				while( !rsEvent->IsEOF( ) )
				{
					iEvents++;

					if( iSelectedEventID < 0 && !bSelectedEventFound )
					// Assume that EventNo order by Descending, and
					// that EventNo is in Date Order. Then pick the first event
					// that has a date less than or equal to todays date.
					{
						eventday.SetDateTime( rsEvent->m_DateYEAR, rsEvent->m_DateMONTH, rsEvent->m_DateDAY, 1, 1, 1 );

						if( eventday <= today )
						{
							iEventID = rsEvent->m_EventID;
							bSelectedEventFound = true;
						}
					}
					else
					{
						iEventID = iSelectedEventID;
					}

					strEvent.Format("%s: %s; %s, %s",
						CConvert::itoa(rsEvent->m_EventNo),
						CFormat::FormatDate(rsEvent->m_DateDAY, rsEvent->m_DateMONTH, rsEvent->m_DateYEAR),
						rsEvent->m_LocationDescription,
						rsEvent->m_EventDescription);
					
					AddSelectBox(strEvent, CConvert::itoa(rsEvent->m_EventID), CConvert::itoa(iEventID));

					rsEvent->MoveNext( );
				}
				EndSelectBox();

			}
//			else
//			{
//				*m_pCtxt << _T("No Events Available\r\n");
//			}

//			rsEvent->Close( );

		}
		catch (CDBException* pEx)
		{
			*m_pCtxt << pEx->m_strError;
			*m_pCtxt << _T("<BR>\r\n");

			pEx->Delete();
		}

		return iEvents;
}

int CHtmlWriter::SelectSeriesBox( 
				   LPCTSTR szTitle, 
				   LPCTSTR szVarName,
				   CRecordset* rs,
				   int iSelectedSeriesID,
				   LPCTSTR szIncludeNone)
{
		int iSeries = 0;

		try
		{
			CSeriesSet* rsSeries = (CSeriesSet*)(rs);

			if( !rsSeries->IsEOF( ) )
			{

				StartSelectBox(szTitle, szVarName);
				if( szIncludeNone != NULL )
					AddSelectBox(szIncludeNone, "0", CConvert::itoa(iSelectedSeriesID));

				while( !rsSeries->IsEOF( ) )
				{
					iSeries++;
					AddSelectBox(rsSeries->m_SeriesDescription, CConvert::itoa(rsSeries->m_SeriesID), CConvert::itoa(iSelectedSeriesID));
					rsSeries->MoveNext( );
				}
				EndSelectBox();

			}
//			else
//			{
//				*m_pCtxt << _T("No Series Available\r\n");
//			}

//			rsSeries->Close( );

		}
		catch (CDBException* pEx)
		{
			*m_pCtxt << pEx->m_strError;
			*m_pCtxt << _T("<BR>\r\n");

			pEx->Delete();
		}

		return iSeries;
}

int CHtmlWriter::SelectPersonBox( 
				   LPCTSTR szTitle, 
				   LPCTSTR szVarName,
				   CRecordset* rs,
				   int iSelectedPersonID,
				   LPCTSTR szIncludeNone)
{
		int iPersons = 0;

		try
		{
			CPersonSet* rsPerson = (CPersonSet*)(rs);

			CString strPerson;

			if( !rsPerson->IsEOF( ) )
			{

				StartSelectBox( szTitle, szVarName);
				if( szIncludeNone != NULL )
					AddSelectBox( szIncludeNone, "0", CConvert::itoa(iSelectedPersonID));

				while( !rsPerson->IsEOF( ) )
				{
					iPersons++;

					strPerson.Format("%s: %s ; %s", 
						CConvert::itoa(rsPerson->m_PersonID),
						CFormat::FormatName(rsPerson->m_LastName, rsPerson->m_FirstName, rsPerson->m_MiddleName),
						CFormat::FormatDate(rsPerson->m_dobDAY, rsPerson->m_dobMONTH, rsPerson->m_dobYEAR)
					);

					AddSelectBox( strPerson, CConvert::itoa(rsPerson->m_PersonID), CConvert::itoa(iSelectedPersonID));
					rsPerson->MoveNext( );
				}
				EndSelectBox();

			}
//			else
//			{
//				*m_pCtxt << _T("No Persons Available\r\n");
//			}

//			rsPerson->Close( );

		}

		catch (CDBException* pEx)
		{
			*m_pCtxt << pEx->m_strError;
			*m_pCtxt << _T("<BR>\r\n");

			pEx->Delete();
		}

		return iPersons;

}


CString CHtmlWriter::GetSelectEventBoxDetails(int iSeriesID,
											  int iMinimumEventID,
											  int iOrderDescending)
{
	return GetSelectEventBoxDetails(iSeriesID, iMinimumEventID, iOrderDescending, FALSE);
}


CString CHtmlWriter::GetSelectEventBoxDetails(int iSeriesID,
											  int iMinimumEventID,
											  int iOrderDescending,
											  int iOpenPreEntry)
{
	CString strSQL;
	CString strOrder;
	CString strOpenPreEntry;

	if(iOpenPreEntry)
		strOpenPreEntry = _T(" AND Event.PreEntryOpen > 0 ");

	if(iOrderDescending)
		strOrder = _T("DESC");
	else
		strOrder = _T("ASC");

	strSQL.Format( "SELECT Series.*, Event.*, EventType.*, Location.* FROM Series, Event, EventType, Location WHERE Series.SeriesID = %d AND Event.EventID >= %d AND Series.SeriesID = Event.SeriesID AND EventType.EventTypeID = Event.EventTypeID AND Location.LocationID = Event.LocationID %s ORDER BY Event.SeriesID, Event.EventNo %s, Event.EventID %s", 
					iSeriesID, 
					iMinimumEventID, 
					strOpenPreEntry,
					strOrder, 
					strOrder);

	return strSQL;
}

CString CHtmlWriter::GetNonEditEventBoxDetails(int iEventID)
{
	CString strSQL;

	strSQL.Format( "SELECT Series.*, Event.*, EventType.*, Location.* FROM Series, Event, EventType, Location WHERE Event.EventID = %d AND	Series.SeriesID = Event.SeriesID AND EventType.EventTypeID = Event.EventTypeID AND Location.LocationID = Event.LocationID ORDER BY Event.SeriesID, Event.EventNo DESC, Event.EventID DESC",
					iEventID );
	return strSQL;
}


void CHtmlWriter::NonEditEvent( 
				  LPCTSTR szTitle, 
				  int nEventNo,
				  LPCTSTR szLocationDescription,
				  LPCTSTR szEventDescription)
{
	CString strEvent;

	strEvent.Format("%s: %s, %s", CConvert::itoa(nEventNo), szLocationDescription, szEventDescription);

	NonEditText( szTitle, strEvent );
}


void CHtmlWriter::ODBCSetupForm(LPCTSTR szPostTo)
{
	CHttpServerProperties prop = CHttpServerProperties( this );

	CStringArray* strDriverDescription = new CStringArray( );
	CStringArray* strDriverAttributes = new CStringArray( );
	CRecordsetEx::GetODBCDrivers(strDriverDescription, strDriverAttributes);

	CStringArray* strDataSourceDescription = new CStringArray( );
	CStringArray* strDataSourceAttributes = new CStringArray( );
	CRecordsetEx::GetODBCDataSources(strDataSourceDescription, strDataSourceAttributes);

	CString strServer = prop.Get(CHtmlKey::ODBC, CHtmlKey::SERVER);
	CString strUid = prop.Get(CHtmlKey::ODBC, CHtmlKey::UID);
	CString strDatabase = prop.Get(CHtmlKey::ODBC, CHtmlKey::DATABASE);
	CString strDriver = prop.Get(CHtmlKey::ODBC, CHtmlKey::DRIVER);
	CString strDsn = prop.Get(CHtmlKey::ODBC, CHtmlKey::DSN);

	strServer = prop.IsEmpty(strServer) ? prop.GetComputerName( ) : strServer;
	strUid = prop.IsEmpty(strUid) ? "" : strUid;
	strDatabase = prop.IsEmpty(strDatabase) ? "" : strDatabase;
	strDriver = prop.IsEmpty(strDriver) ? CRecordsetEx::driverMSSQLServer : strDriver;
	strDsn = prop.IsEmpty(strDsn) ? CRecordsetEx::noDSN : strDsn;

	//CString strJavaScript;
	//LoadLongResource(strJavaScript, IDS_HTML_DBCONFIG);
	//*this << _T(strJavaScript);

	*this << _T("Please specify your database configuration.<BR>\r\n");

	int i;

	StartForm("Database Configuration", szPostTo);
	NonEditText("URL", GetPathName( ));
	HiddenText("URL", GetPathName( ));
	EditTextBoxSmall("Server", "Server", strServer);
	EditTextBoxSmall("UID", "UID", strUid);
	PasswordBox("PWD", "PWD", "");
	EditTextBoxLarge("Database", "Database", strDatabase);

	StartSelectBox("Driver", "Driver");
	AddSelectBox(CRecordsetEx::useDSN, CRecordsetEx::useDSN, strDriver);
	for( i = 0; i < strDriverDescription->GetSize( ) ; i++ )
	{
		AddSelectBox(strDriverDescription->GetAt(i), strDriverDescription->GetAt(i), strDriver);
	}
	EndSelectBox();

	StartSelectBox("DSN", "DSN");
	AddSelectBox(CRecordsetEx::noDSN, CRecordsetEx::noDSN, strDsn);
	for( i = 0; i < strDataSourceDescription->GetSize( ) ; i++ )
	{
		AddSelectBox(strDataSourceDescription->GetAt(i), strDataSourceDescription->GetAt(i), strDsn);
	}
	EndSelectBox();

	HorizontalRule();
	
	SubmitButton(CHtmlKey::Save);
	EndForm();


	delete strDriverDescription;
	delete strDriverAttributes;

	delete strDataSourceDescription;
	delete strDataSourceAttributes;
}

CString CHtmlWriter::GetMFCIsapiCommand(LPCTSTR szAction)
{
	CString str;

	str += _T("      <input type=\"hidden\" name=\"MFCIsapiCommand\" value=\"");
	str += _T(szAction);
	str += _T("\">\r\n");

	return str;
}

CString CHtmlWriter::GetAction(LPCTSTR szAction)
{
	CString str = GetFileName( );

	str += _T( "?" );
	//str += _T( szAction );

	return str;
}

void CHtmlWriter::DefaultPage(LPCTSTR szButton, LPCTSTR szAction)
{
	CString strPage;
	CString strOutput;

	CString strBuildNo;
	CString strBuildDate;
	CString strReleaseNo;

	CUtil::LoadLongResource(strPage, IDS_HTML_DEFAULT);

	CUtil::LoadLongResource(strBuildNo,   IDS_BUILD_NO);
	CUtil::LoadLongResource(strBuildDate, IDS_BUILD_DATE);
	CUtil::LoadLongResource(strReleaseNo, IDS_RELEASE_NO);

	//strBuildDate.Format("%s %s", __TIME__, __DATE__ );

	strOutput.Format(strPage, _T(strReleaseNo),
							  _T(strBuildNo),
							  _T(strBuildDate),
							  _T(GetAction(szAction)),
							  _T(GetMFCIsapiCommand(szAction)),
							  _T(szButton));

	*m_pCtxt << _T(strOutput);
}
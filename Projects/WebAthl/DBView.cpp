// CDBView.cpp : implementation file
//

#include "stdafx.h"

#include "resource.h"

#include "BitMaskEnum.h"
#include "DBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DBView

/////////////////////////////////////////////////////////////////////////////
// Constructor

CDBView::CDBView( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CDBView::~CDBView( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CDBView::GetName()
{
	return CDBView::GetName(m_dwItemEnum);
}

UINT CDBView::GetId()
{
	return CDBView::GetId(m_dwItemEnum);
}

CString CDBView::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CDBView::LatestFinancial :
			return "LatestFinancial";
			break;
		default :
			return "";
			break;
	}

}

UINT CDBView::GetId(DWORD dwItem)
{

	switch( dwItem )
	{
		case CDBView::LatestFinancial :
			return IDS_SQL_CR_LATESTFINANCIAL;
			break;
		default :
			return 0;
			break;
	}

}


// CMaintainDatabase.cpp : implementation file
//

#include "stdafx.h"

#include "BitMaskEnum.h"
#include "MaintainDatabase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MaintainDatabase

/////////////////////////////////////////////////////////////////////////////
// Constructor

CMaintainDatabase::CMaintainDatabase( )
	: CBitMaskEnum( )
{
}

/////////////////////////////////////////////////////////////////////////////
// Destructor

//CMaintainDatabase::~CMaintainDatabase( )
//{
//}

/////////////////////////////////////////////////////////////////////////////
// Member functions

CString CMaintainDatabase::GetName()
{
	return CMaintainDatabase::GetName(m_dwItemEnum);
}

CString CMaintainDatabase::GetTitle()
{
	return CMaintainDatabase::GetTitle(m_dwItemEnum);
}

CString CMaintainDatabase::GetMessage()
{
	return CMaintainDatabase::GetMessage(m_dwItemEnum);
}

CString CMaintainDatabase::GetName(DWORD dwItem)
{

	switch( dwItem )
	{
		case CMaintainDatabase::CreateTables :
			return "Create Tables";
			break;
		case CMaintainDatabase::CreateViews :
			return "Create Views";
			break;
		case CMaintainDatabase::ExportData :
			return "Export Data";
			break;
		case CMaintainDatabase::ImportData :
			return "Import Data";
			break;
		case CMaintainDatabase::CreateForeignKeys :
			return "Create Foreign Keys";
			break;
		case CMaintainDatabase::DropForeignKeys :
			return "Drop Foreign Keys";
			break;
//		case CMaintainDatabase::CreateStoredProcedures :
//			return "Create Stored Procedures";
//			break;
		default :
			return "";
			break;
	}

}


CString CMaintainDatabase::GetTitle(DWORD dwItem)
{

	switch( dwItem )
	{
		case CMaintainDatabase::CreateViews :
			return "Database Views";
			break;
		case CMaintainDatabase::CreateTables :
		case CMaintainDatabase::ExportData :
		case CMaintainDatabase::ImportData :
			return "Database Tables";
			break;
		case CMaintainDatabase::CreateForeignKeys :
		case CMaintainDatabase::DropForeignKeys :
			return "Foreign Keys";
			break;
//		case CMaintainDatabase::CreateStoredProcedures :
//			return "Stored Procedures";
//			break;
		default :
			return "";
			break;
	}

}


CString CMaintainDatabase::GetMessage(DWORD dwItem)
{

	switch( dwItem )
	{
		case CMaintainDatabase::CreateTables :
			return "Select the Tables you wish to Create.<BR><BR>\r\n<B>Warning</B>: Any data currently in the Tables you choose, will be destroyed.<BR><BR>\r\n<B>Note</B>: The <B><I>Create Tables</I></B> utility only Creates Primary Keys and Candidate Keys, is does <B><I>not</I></B> Create Foreign Keys, you should run the <B><I>Create Foreign Keys</I></B> Maintenance utility (to maintain Referential Integrity) after you run the Create Tables.<BR>\r\n";
			break;
		case CMaintainDatabase::CreateViews :
			return "Select the Views you wish to Create.<BR>\r\n";
			break;
		case CMaintainDatabase::ExportData :
			return "Select the Tables you wish to Export.<BR>\r\n";
			break;
		case CMaintainDatabase::ImportData :
			return "Select the Tables you wish to Import.<BR><BR>\r\n<B>Warning</B>: Import will <B><I>append</I></B> data to the database, <B><I>not</I></B> replace.<BR>If you need to replace the current data, then you should run the <B><I>Create Tables</I></B> Maintenance utility (to erase the current data) before you run the <B><I>Import</I></B>.<BR>\r\n";
			break;
		case CMaintainDatabase::CreateForeignKeys :
			return "Select the Foreign Keys you wish to Create.<BR>\r\n";
			break;
		case CMaintainDatabase::DropForeignKeys :
			return "Select the Foreign Keys you wish to Drop.<BR>\r\n";
			break;
//		case CMaintainDatabase::CreateStoredProcedures :
//			return "Select the Stored Procedures you wish to Create.<BR>\r\n";
//			break;
		default :
			return "";
			break;
	}

}


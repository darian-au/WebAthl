#if !defined(AFX_HTMLKEY_H__INCLUDED_)
#define AFX_HTMLKEY_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CHtmlKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHtmlKey

class CHtmlKey
{

	public:

		// Constructor
		//CHtmlKey( );	

		// Destructor
		//~CHtmlKey( );

		// Member functions

		// Static functions

		// Member variables

		// Static variables

		// Buttons
		static LPCTSTR Submit;
		static LPCTSTR Cancel;
		static LPCTSTR Select;
		static LPCTSTR Login;
		static LPCTSTR LogOff;
		static LPCTSTR Add;
		static LPCTSTR Save;
		static LPCTSTR Delete;
		static LPCTSTR Run;
		static LPCTSTR Contact;
		static LPCTSTR Next;
		static LPCTSTR Search;
		static LPCTSTR Revoke;
		static LPCTSTR Remove;
		static LPCTSTR Continue;

		// Cookies
		static LPCTSTR BackLink;
		static LPCTSTR FrwdLink;
		static LPCTSTR Heading;
		static LPCTSTR OrgName;
		static LPCTSTR LoginName;
		static LPCTSTR Password;
		static LPCTSTR SeriesID;
		static LPCTSTR EventID;
		static LPCTSTR PersonID;
		static LPCTSTR IsUtil;
		static LPCTSTR DWProc;
		static LPCTSTR ResultsEntry;
		static LPCTSTR IsSecured;
		static LPCTSTR IsOptions;
		static LPCTSTR IsResultsEntry;

		// Keys
		static LPCTSTR UtilitiesChangeIsGroup;
		static LPCTSTR UtilitiesChangeIsEligibility;

		// Registry Keys
		static LPCTSTR AgeGroup;
			static LPCTSTR MaxJunior;
			static LPCTSTR JuniorGroup;
			static LPCTSTR MinVeteran;
			static LPCTSTR VeteranGroup;
			static LPCTSTR NullDoB;

		static LPCTSTR Processing;
			static LPCTSTR TimeOut;

		static LPCTSTR Appearance;
			static LPCTSTR Font;
			static LPCTSTR BackgroundColor;
			static LPCTSTR MenuColor;
			static LPCTSTR Logo;
			static LPCTSTR BackgroundImage;
			static LPCTSTR MenuImage;
			static LPCTSTR StyleSheet;

		static LPCTSTR Cryptography;
			static LPCTSTR Enabled;
			//static LPCTSTR Password;

		static LPCTSTR UserAccess;
			//static LPCTSTR Enabled;

		static LPCTSTR Navigation;
			static LPCTSTR ExitURL;

		static LPCTSTR PersonSearch;
			static LPCTSTR LastName;
			static LPCTSTR FirstName;
			static LPCTSTR MiddleName;
			static LPCTSTR DateOfBirth;
			static LPCTSTR Sex;

		static LPCTSTR Properties;
			//static LPCTSTR Enabled;

		static LPCTSTR ODBC;
			static LPCTSTR SERVER;
			static LPCTSTR UID;
			static LPCTSTR PWD;
			static LPCTSTR DATABASE;
			static LPCTSTR DRIVER;
			static LPCTSTR DSN;
			static LPCTSTR BackupFolder;

		static LPCTSTR License;
			static LPCTSTR No;
			static LPCTSTR Name;
			static LPCTSTR Key;


	private:

		// Member variables

};

#endif // !defined(AFX_HTMLKEY_H__INCLUDED_)

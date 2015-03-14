// GenKey.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GenKeyEx.h"

int main(int argc, char* argv[])
{
	char szKeyMsg[4000];
	char szKey[4000];

	int nStatus = GenKeyEx(argv, szKeyMsg, szKey);

	cout << szKeyMsg << endl;

	return nStatus;
}
// IniFile.cpp: Implementierung der Klasse CIniFile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fs_ini_file.h"

typedef map<string,	CIniFileSection>::iterator CIniI;
typedef map<string, string>::iterator SI;


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile()
{
}

CIniFile::~CIniFile()
{
}

int CIniFile::LoadFile(const char* filename)
{
	Clear();

	return(InsertFile(filename, NULL));
}


void CIniFile::Clear()
{

	sections.clear();	
}

CIniFileSection::CIniFileSection()
{
	values.clear();
};

CIniFileSection::~CIniFileSection()
{
	values.clear();
};

int CIniFile::InsertFile(const char *filename, const char *Section)
{
	if(filename==NULL) return 1;
	if(strlen(filename)==NULL) return 1;

	fstream file;

	file.open(filename, ios::in);
	if(!file.good()) return 2;

	// file.eatwhite();

	char cSec[256];
	char cLine[4096];

	memset(cSec, 0, 256);
	memset(cLine, 0, 4096);

	while(!file.eof())
	{
		file.getline(cLine, 4096);
		
		if(strchr(cLine, 13))
			(strchr(cLine, 13))[0]=0;
		
		// first we do comments out
		if(strchr(cLine, ';'))
		{
			// comment there!!!
			cLine[strchr(cLine, ';')-cLine]=0;
		}

		if( strchr(cLine, '[') &&  (!strchr(cLine, '=') || (strchr(cLine, '=')>strchr(cLine, '[') )) )
		{
			if((Section!=NULL) && strcmp(Section,cSec)==NULL) return 0; // the section we want to insert is finished

			strcpy(cLine, strchr(cLine, '[')+1);
			cLine[strchr(cLine, ']')-cLine]=0;

			strcpy(cSec, cLine);
			
		}
		else if(strchr(cLine, '=') && strlen(cSec)>0)
		{
			if(Section==NULL || strcmp(cSec,Section)==NULL)
			{
				// a value is set and we have a valid current section!
				char value[4096];
				memset(value,0,4096);
				strcpy(value, strchr(cLine, '=')+1);
				cLine[strchr(cLine, '=')-cLine]=0;
				sections[cSec].values[cLine]=value;
			}			
		}
	
	}

	file.close();

	return 0;
}

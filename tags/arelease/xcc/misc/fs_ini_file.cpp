// IniFile.cpp: Implementierung der Klasse CIniFile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fs_ini_file.h"

/*
bool SortDummy::operator()(const string& x, const string& y) const{
	// the length is more important than spelling (numbers!!!)...
	if(x.length() < y.length()) 
		return true;
	if(x.length() == y.length())
	{		
		if(x < y) 
			return true;
	}
	return false;
	
}
*/

typedef map<string,	CIniFileSection>::iterator CIniI;
typedef map<string, string/*, SortDummy*/>::iterator SI;


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CIniFile::CIniFile()
{
	Clear();
}

CIniFile::~CIniFile()
{
	Clear();
}

WORD CIniFile::LoadFile(const char* filename)
{
	Clear();

	if(filename==NULL) return 1;
	if(strlen(filename)==NULL) return 1;

	strcpy(m_filename, filename);

	return(InsertFile(filename, NULL));
	
}


void CIniFile::Clear()
{

	sections.clear();	
}

CIniFileSection::CIniFileSection(){
	values.clear();
};

CIniFileSection::~CIniFileSection(){
	values.clear();
};

WORD CIniFile::InsertFile(const char *filename, const char *Section)
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

CIniFileSection* CIniFile::GetSection(unsigned int index)
{
	if (index>sections.size()-1) return NULL;

	CIniI i=sections.begin();
	for (int e=0;e<index;e++)
		i++;
	
	return &i->second;
}

string* CIniFileSection::GetValue(unsigned int index)
{
	if (index>values.size()-1) return NULL;

	SI i=values.begin();
	for (int e=0;e<index;e++)
		i++;
	
	return &i->second;
}

const string* CIniFile::GetSectionName(unsigned int index)
{
	if (index>sections.size()-1) return NULL;

	CIniI i=sections.begin();
	for (int e=0;e<index;e++)
		i++;
	
	return &(i->first);
}

const string* CIniFileSection::GetValueName(unsigned int index)
{
	if (index>values.size()-1) return NULL;

	SI i=values.begin();
	for (int e=0;e<index;e++)
		i++;

	
	
	return &(i->first);
}

BOOL CIniFile::SaveFile(const char *Filename)
{
	fstream file;

	file.open(Filename, ios::out | ios::trunc);
	
	int i;
	for(i=0;i<sections.size();i++)
	{
		file << "[" << GetSectionName(i)->data() << "]" << endl;
		int e;
		for(e=0;e<GetSection(i)->values.size();e++)
		{
			file << GetSection(i)->GetValueName(e)->data() << "=" << GetSection(i)->GetValue(e)->data() << endl;
		}
		file << endl;
	}

	return TRUE;
}


int CIniFileSection::FindValue(string sval)
{
	int i;
	for(i=0;i<values.size();i++)
	{
		
		if(sval==GetValue(i)->data())
			return i;
		//MessageBox(0,sval.data(),GetValue(i)->data(),0);
	}
	return -1;
}

int CIniFileSection::FindName(string sval)
{
	int i;
	for(i=0;i<values.size();i++)
	{
		
		if(sval==GetValueName(i)->data())
			return i;
		//MessageBox(0,sval.data(),GetValue(i)->data(),0);
	}
	return -1;
}

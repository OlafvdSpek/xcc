// MIXOptions.cpp : implementation file
//

#include "stdafx.h"
#include "XCC MIX Editor.h"
#include "MIXOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMIXOptions dialog


CMIXOptions::CMIXOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CMIXOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMIXOptions)
	m_check_checksum = FALSE;
	m_check_encrypted = FALSE;
	m_combo_game = -1;
	//}}AFX_DATA_INIT
}


void CMIXOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMIXOptions)
	DDX_Check(pDX, IDC_CHECK_CHECKSUM, m_check_checksum);
	DDX_Check(pDX, IDC_CHECK_ENCRYPTED, m_check_encrypted);
	DDX_CBIndex(pDX, IDC_COMBO_GAME, m_combo_game);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMIXOptions, CDialog)
	//{{AFX_MSG_MAP(CMIXOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIXOptions message handlers

void CMIXOptions::get(t_game& game, bool& encrypted, bool& checksum)
{
	game = static_cast<t_game>(m_combo_game);
	encrypted = m_check_encrypted;
	checksum = m_check_checksum;
}

void CMIXOptions::set(t_game game, bool encrypted, bool checksum)
{
	m_combo_game = game;
	m_check_encrypted = encrypted;
	m_check_checksum = checksum;
}
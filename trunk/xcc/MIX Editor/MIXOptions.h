#pragma once

#include "mix_file.h"
#include "resource.h"

class CMIXOptions : public CDialog
{
public:
	void get(t_game& game, bool& encrypted, bool& checksum);
	void set(t_game game, bool encrypted, bool checksum);
	CMIXOptions(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CMIXOptions)
	enum { IDD = IDD_OPTIONS };
	BOOL	m_check_checksum;
	BOOL	m_check_encrypted;
	int		m_combo_game;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMIXOptions)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMIXOptions)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

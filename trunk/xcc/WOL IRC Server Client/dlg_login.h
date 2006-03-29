#if !defined(AFX_DLG_LOGIN_H__06C1065C_6491_4DBA_B0B2_680543B94CCA__INCLUDED_)
#define AFX_DLG_LOGIN_H__06C1065C_6491_4DBA_B0B2_680543B94CCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class Cdlg_login : public ETSLayoutDialog
{
public:
	struct t_nick
	{
		string name;
		string password;
	};
	struct t_game
	{
		int gsku;
		string serial;
	};


	typedef vector<t_nick> t_nicks;
	typedef vector<t_game> t_games;

	void add_game(const string& reg_key, int game, int gsku);
	Cdlg_login(CWnd* pParent = NULL);

	void ipa(int v)
	{
		m_ipa = v;
	}

	//{{AFX_DATA(Cdlg_login)
	enum { IDD = IDD_LOGIN };
	CComboBox	m_game;
	CComboBox	m_user;
	CString	m_edit;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(Cdlg_login)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(Cdlg_login)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	t_games m_games;
	t_nicks m_nicks;
	int m_ipa;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_DLG_LOGIN_H__06C1065C_6491_4DBA_B0B2_680543B94CCA__INCLUDED_)

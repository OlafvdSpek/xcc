#pragma once

#include <cc_structures.h>
#include "resource.h"

class Cdlg_login: public ETSLayoutDialog
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

	void add_game(const string& reg_key, ::t_game game, int gsku);
	Cdlg_login(CWnd* pParent = NULL);

	enum { IDD = IDD_LOGIN };
	CComboBox	m_game;
	CComboBox	m_user;
	CString	m_edit;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
private:
	t_games m_games;
	t_nicks m_nicks;
};

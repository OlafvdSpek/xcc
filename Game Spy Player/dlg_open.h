#pragma once

#include "ListCtrlEx.h"
#include "resource.h"
#include "xif_key.h"

class Cdlg_open : public ETSLayoutDialog
{
public:
	void sort_players(int i);
	void insert_replays_columns();
	void insert_players_columns();
	int replay_compare(int id_a, int id_b);
	int player_compare(int id_a, int id_b);
	void sort_replays(int i, bool reverse);
	Cxif_key export_cache();
	void import_cache(const Cxif_key& key);
	string fname();
	Cdlg_open(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(Cdlg_open)
	enum { IDD = IDD_OPEN };
	CListCtrlEx	m_players;
	CButton	m_ok;
	CListCtrlEx	m_replays;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(Cdlg_open)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cdlg_open)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoReplays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedReplays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkReplays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickReplays(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoPlayers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedPlayers(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickPlayers(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	typedef set<string> t_player_set;
	typedef set<int> t_replay_set;

	struct t_map_entry
	{
		string dir;
		string name;
		int gid;
		int size;
		t_player_set players;
		string scenario;
	};

	struct t_player_map_entry
	{
		string player;
		t_replay_set replays;
	};

	typedef map<int, t_map_entry> t_map;
	typedef map<int, t_player_map_entry> t_player_map;
	typedef map<string, int> t_reverse_player_map;

	void insert_player(const string& player, int replay);
	void insert_players(const t_player_set& players, int replay);

	string m_fname;
	t_map m_map;
	t_player_map m_player_map;
	t_reverse_player_map m_reverse_player_map;
	int m_sort_column;
	bool m_sort_reverse;
	int m_players_sort_column;
};

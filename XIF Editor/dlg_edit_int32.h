#include <string>

using namespace std;

class Cdlg_edit_int32 : public CDialog
{
// Construction
public:
	int get();
	void set(const string& key, int value);
	Cdlg_edit_int32(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdlg_edit_int32)
	enum { IDD = IDD_EDIT_INT32 };
	CString	m_key;
	int		m_value;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdlg_edit_int32)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdlg_edit_int32)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#include "stdafx.h"
#include "dlg_serials.h"

IMPLEMENT_DYNAMIC(Cdlg_serials, ETSLayoutDialog)

Cdlg_serials::Cdlg_serials(CWnd* pParent /*=NULL*/)
	: ETSLayoutDialog(Cdlg_serials::IDD, pParent)
{
}

void Cdlg_serials::DoDataExchange(CDataExchange* pDX)
{
	ETSLayoutDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cdlg_serials, ETSLayoutDialog)
END_MESSAGE_MAP()

BOOL Cdlg_serials::OnInitDialog() 
{
	CreateRoot(VERTICAL)
		<< item(IDC_EDIT, GREEDY)
		<< (pane(HORIZONTAL, ABSOLUTE_VERT)
				<< itemGrowing(HORIZONTAL)
				<< item(IDCANCEL, NORESIZE)
			)
		;
	ETSLayoutDialog::OnInitDialog();
	return true;
}

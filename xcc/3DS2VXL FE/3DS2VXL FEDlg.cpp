// 3DS2VXL FEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "3DS2VXL FE.h"
#include "3DS2VXL FEDlg.h"
#include "3ds2vxl_fe_ini_reader.h"

#include <fstream>
#include "file32.h"
#include "fname.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DS2VXLFEDlg dialog

CMy3DS2VXLFEDlg::CMy3DS2VXLFEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy3DS2VXLFEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy3DS2VXLFEDlg)
	m_destination = _T("");
	m_source = _T("");
	m_skybox = _T("");
	m_sgal = FALSE;
	m_sgn = FALSE;
	m_estimate_origin = FALSE;
	m_flip_x = FALSE;
	m_flip_y = FALSE;
	m_swap_xy = FALSE;
	m_textures = FALSE;
	m_size = 0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3DS2VXLFEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy3DS2VXLFEDlg)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Text(pDX, IDC_DESTINATION, m_destination);
	DDX_Text(pDX, IDC_SOURCE, m_source);
	DDX_Text(pDX, IDC_SKYBOX, m_skybox);
	DDX_Check(pDX, IDC_SGAL, m_sgal);
	DDX_Check(pDX, IDC_SGN, m_sgn);
	DDX_Check(pDX, IDC_ESTIMATE_ORIGIN, m_estimate_origin);
	DDX_Check(pDX, IDC_FLIP_X, m_flip_x);
	DDX_Check(pDX, IDC_FLIP_Y, m_flip_y);
	DDX_Check(pDX, IDC_SWAP_XY, m_swap_xy);
	DDX_Check(pDX, IDC_TEXTURES, m_textures);
	DDX_Text(pDX, IDC_MAX_SIZE, m_size);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy3DS2VXLFEDlg, CDialog)
	//{{AFX_MSG_MAP(CMy3DS2VXLFEDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SKYBOX_BROWSE, OnSkyboxBrowse)
	ON_BN_CLICKED(IDC_SOURCE_BROWSE, OnSourceBrowse)
	ON_BN_CLICKED(IDC_DESTINATION_BROWSE, OnDestinationBrowse)
	ON_EN_UPDATE(IDC_SOURCE, update_buttons)
	ON_EN_UPDATE(IDC_SKYBOX, update_buttons)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DS2VXLFEDlg message handlers

BOOL CMy3DS2VXLFEDlg::OnInitDialog()
{
	Cfname fname = GetModuleFileName();
	fname.set_ext(".ini");
	m_fname = fname;
	C3ds2vxl_fe_ini_reader ir;	
	Cfile32 f;
	if (!f.open_read(m_fname))
	{
		int cb_d = f.get_size();
		byte* d = new byte[cb_d];
		if (!f.read(d, cb_d))
			ir.process(d, cb_d);
		delete[] d;
		f.close();
	}
	t_options options = ir.options();
	m_destination = options.destination.c_str();
	m_estimate_origin = options.estimate_origin;
	m_flip_x = options.flip_x;
	m_flip_y = options.flip_y;
	m_sgal = options.sgal;
	m_sgn = options.sgn;
	m_size = options.size;
	m_skybox = options.skybox.c_str();
	m_source = options.source.c_str();
	m_swap_xy = options.swap_xy;
	m_textures = options.textures;
	
	CDialog::OnInitDialog();

	update_buttons();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	{
		// Create the ToolTip control.
		m_tooltip.Create(this);
		m_tooltip.Activate(TRUE);
		m_tooltip.AddTool(GetDlgItem(IDC_FLIP_X), "Change this if the model is facing backwards.");
		m_tooltip.AddTool(GetDlgItem(IDC_FLIP_Y), "Change this if you get a sort of x-ray vision effect.");
		m_tooltip.AddTool(GetDlgItem(IDC_SWAP_XY), "Change this if the model is facing sideways.");
		m_tooltip.AddTool(GetDlgItem(IDC_ESTIMATE_ORIGIN), "Change this if the reference ellipsoids are not centered in the center of mass of the model. Neither way may be what you want but just pick the best.");
		m_tooltip.AddTool(GetDlgItem(IDC_SGN), "I recommend you keep this off.");
		m_tooltip.AddTool(GetDlgItem(IDC_SGAL), "Not working yet.");
		m_tooltip.AddTool(GetDlgItem(IDC_TEXTURES), "Working partially and only in the viewer. Try deactivating if the model looks full of static.");
	}
	return true;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy3DS2VXLFEDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMy3DS2VXLFEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int browse_for_file(string& fname, string filter)
{    
	return 1;
}

void CMy3DS2VXLFEDlg::OnSkyboxBrowse() 
{
	CFileDialog dlg(true, "tga", m_skybox, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "TGA files (*.tga)|*.tga|", this);
	if (IDOK == dlg.DoModal())
	{
		m_skybox = dlg.GetPathName();
		UpdateData(false);
		update_buttons();
	}	
}

void CMy3DS2VXLFEDlg::OnSourceBrowse() 
{
	CFileDialog dlg(true, "3ds", m_source, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "3DS files (*.3ds)|*.3ds|", this);
	if (IDOK == dlg.DoModal())
	{
		m_source = dlg.GetPathName();
		UpdateData(false);
		update_buttons();
	}	
}

void CMy3DS2VXLFEDlg::OnDestinationBrowse() 
{
	CFileDialog dlg(false, "vxl", m_destination, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST, "VXL files (*.vxl)|*.vxl|", this);
	if (IDOK == dlg.DoModal())
	{
		m_destination = dlg.GetPathName();
		UpdateData(false);
	}	
}

void CMy3DS2VXLFEDlg::OnOK() 
{
	UpdateData(true);
	t_options options;
	options.destination = m_destination;
	options.estimate_origin = m_estimate_origin;
	options.flip_x = m_flip_x;
	options.flip_y = m_flip_y;
	options.sgal = m_sgal;
	options.sgn = m_sgn;
	options.size = m_size;
	options.skybox = m_skybox;
	options.source = m_source;
	options.swap_xy = m_swap_xy;
	options.textures = m_textures;
	write_ini(options, ofstream(m_fname.c_str()));
	Cfname fname = "3ds2vxl.exe";
	fname.set_path(GetModuleFileName().get_path());
	ShellExecute(m_hWnd, "open", static_cast<string>(fname).c_str(), ("-ini " + m_fname).c_str(), NULL, SW_SHOW);
}

void CMy3DS2VXLFEDlg::update_buttons()
{
	UpdateData(true);
	m_ok.EnableWindow(Cfname(static_cast<string>(m_source)).exists() || Cfname(static_cast<string>(m_skybox)).exists());
}

BOOL CMy3DS2VXLFEDlg::PreTranslateMessage(MSG* pMsg)
{
	m_tooltip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

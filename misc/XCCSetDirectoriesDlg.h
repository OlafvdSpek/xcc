/*
    XCC Utilities and Library
    Copyright (C) 2000  Olaf van der Spek  <olafvdspek@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

class CXCCSetDirectoriesDlg : public CDialog
{
public:
	CXCCSetDirectoriesDlg(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(CXCCSetDirectoriesDlg)
	enum { IDD = IDD_XCCDIRECTORIES };
	CString	m_dir1;
	CString	m_dir2;
	CString	m_cd_dir;
	CString	m_data_dir;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CXCCSetDirectoriesDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//{{AFX_MSG(CXCCSetDirectoriesDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

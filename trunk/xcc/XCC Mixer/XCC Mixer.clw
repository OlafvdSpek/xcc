; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CXSE_dlg
LastTemplate=CListCtrl
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "xcc mixer.h"
LastPage=0

ClassCount=14
Class1=CMainFrame
Class2=CXCCMixerApp
Class3=CAboutDlg
Class4=CXCCMixerDoc
Class5=CXCCMixerView
Class6=CXCCFileView

ResourceCount=9
Resource1=IDR_MAINFRAME (English (U.S.))
Resource2=IDD_SEARCH_FILE
Class7=CDirectoriesDlg
Resource3=IDD_DIRECTORIES
Class8=CResizeDlg
Resource4=IDD_RESIZE
Class9=CSearchFileDlg
Resource5=CG_IDR_POPUP_MIX_VIEW
Class10=CXCCObjectExtractorDlg
Resource6=IDD_XSTE_EDIT
Class11=CXSTE_dlg
Resource7=IDD_XCC_OBJECT_EXTRACTOR
Class12=CXSTE_edit_dlg
Resource8=IDD_XSTE
Class13=CXSE_dlg
Class14=CXSE_list
Resource9=IDD_XSE

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=ID_LAUNCH_XSE
Filter=T
VirtualFilter=fWC

[CLS:CXCCMixerApp]
Type=0
BaseClass=CWinApp
HeaderFile=XCC Mixer.h
ImplementationFile=XCC Mixer.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=XCC Mixer.cpp
ImplementationFile=XCC Mixer.cpp
LastObject=CAboutDlg

[CLS:CXCCMixerDoc]
Type=0
BaseClass=CDocument
HeaderFile=XCC MixerDoc.h
ImplementationFile=XCC MixerDoc.cpp

[CLS:CXCCMixerView]
Type=0
BaseClass=CListView
HeaderFile=XCC MixerView.h
ImplementationFile=XCC MixerView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CXCCMixerView

[CLS:CXCCFileView]
Type=0
BaseClass=CScrollView
HeaderFile=XCCFileView.h
ImplementationFile=XCCFileView.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[MNU:CG_IDR_POPUP_MIX_VIEW]
Type=1
Class=?
Command1=ID_POPUP_OPEN
Command2=ID_POPUP_OPEN_FOR_EDIT
Command3=ID_POPUP_OPEN_WITH_FINALSUN
Command4=ID_POPUP_PLAY
Command5=ID_POPUP_EXTRACT
Command6=ID_POPUP_COPY
Command7=ID_POPUP_COPY_AS_AUD
Command8=ID_POPUP_COPY_AS_AVI
Command9=ID_POPUP_COPY_AS_CPS
Command10=ID_POPUP_COPY_AS_CSV
Command11=ID_POPUP_COPY_AS_HTML
Command12=ID_POPUP_COPY_AS_HVA
Command13=ID_POPUP_COPY_AS_MAP_TS_PREVIEW
Command14=ID_POPUP_COPY_AS_PAL
Command15=ID_POPUP_COPY_AS_PAL_JASC
Command16=ID_POPUP_COPY_AS_PCX
Command17=ID_POPUP_COPY_AS_PNG
Command18=ID_POPUP_COPY_AS_SHP
Command19=ID_POPUP_COPY_AS_SHP_TS
Command20=ID_POPUP_COPY_AS_TEXT
Command21=ID_POPUP_COPY_AS_TMP_TS
Command22=ID_POPUP_COPY_AS_VXL
Command23=ID_POPUP_COPY_AS_WAV
Command24=ID_POPUP_COPY_AS_WSA
Command25=ID_POPUP_COPY_AS_XIF
Command26=ID_POPUP_IMPORT_INTO_TS
Command27=ID_POPUP_IMPORT_INTO_RA2
Command28=ID_POPUP_REFRESH
Command29=ID_POPUP_RESIZE
Command30=ID_POPUP_DELETE
CommandCount=30

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_CREATE_SFL
Command5=ID_FILE_FOUND_UPDATE
Command6=ID_FILE_SEARCH
Command7=ID_APP_EXIT
Command8=ID_CONVERSION_SPLIT_SHADOWS
Command9=ID_VIEW_GAME_TD
Command10=ID_VIEW_GAME_RA
Command11=ID_VIEW_GAME_TS
Command12=ID_VIEW_GAME_AUTO
Command13=ID_VIEW_PALET_UPDATE
Command14=ID_VIEW_PALET_AUTO
Command15=ID_VIEW_PALET_PREV
Command16=ID_VIEW_PALET_NEXT
Command17=ID_VIEW_PALET_CONVERT_FROM_TD
Command18=ID_VIEW_PALET_CONVERT_FROM_RA
Command19=ID_VIEW_PALET_USE_FOR_CONVERSION
Command20=ID_VIEW_VOXEL_NORMAL
Command21=ID_VIEW_VOXEL_SURFACE_NORMALS
Command22=ID_VIEW_VOXEL_DEPTH_INFORMATION
Command23=ID_VIEW_DIRECTX_OPTIONS
Command24=ID_VIEW_DIRECTORIES
Command25=ID_INTERNET_FS_SITE
Command26=ID_INTERNET_GENIUS_SITE
Command27=ID_INTERNET_SE_SITE
Command28=ID_INTERNET_XCC_SITE
Command29=ID_UTILITIES_XCC_AV_PLAYER
Command30=ID_UTILITIES_XCC_EDITOR
Command31=ID_UTILITIES_XCC_MIX_EDITOR
Command32=ID_LAUNCH_XOE_TS
Command33=ID_LAUNCH_XOE_RA2
Command34=ID_LAUNCH_XSE
Command35=ID_LAUNCH_XSTE
Command36=ID_LAUNCH_XCC_THEME_WRITER
Command37=ID_UTILITIES_FS
Command38=ID_UTILITIES_SE
Command39=ID_UTILITIES_SEMM
Command40=ID_LAUNCH_DUNE2
Command41=ID_LAUNCH_TD
Command42=ID_LAUNCH_RA
Command43=ID_LAUNCH_DUNE2000
Command44=ID_LAUNCH_TS
Command45=ID_LAUNCH_RA2
CommandCount=45

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_VIEW_PALET_PREV
Command2=ID_VIEW_PALET_NEXT
Command3=ID_FILE_CLOSE
Command4=ID_FILE_NEW
Command5=ID_FILE_OPEN
Command6=ID_POPUP_REFRESH
CommandCount=6

[DLG:IDD_DIRECTORIES]
Type=1
Class=CDirectoriesDlg
ControlCount=22
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_DUNE2,edit,1350631552
Control13=IDC_TD_PRIMARY,edit,1350631552
Control14=IDC_TD_SECONDARY,edit,1350631552
Control15=IDC_RA,edit,1350631552
Control16=IDC_DUNE2000,edit,1350633600
Control17=IDC_TS,edit,1350633600
Control18=IDC_RA2,edit,1350633600
Control19=IDC_DATA,edit,1350631552
Control20=IDC_CD,edit,1350631552
Control21=IDC_RESET_DATA,button,1342242816
Control22=IDC_RESET_CD,button,1342242816

[CLS:CDirectoriesDlg]
Type=0
HeaderFile=DirectoriesDlg.h
ImplementationFile=DirectoriesDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RESET_DATA
VirtualFilter=dWC

[DLG:IDD_RESIZE]
Type=1
Class=CResizeDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CX,edit,1350639744
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CY,edit,1350639744
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[CLS:CResizeDlg]
Type=0
HeaderFile=ResizeDlg.h
ImplementationFile=ResizeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CResizeDlg
VirtualFilter=dWC

[DLG:IDD_SEARCH_FILE]
Type=1
Class=CSearchFileDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_FILENAME,edit,1350631552
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[CLS:CSearchFileDlg]
Type=0
HeaderFile=SearchFileDlg.h
ImplementationFile=SearchFileDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSearchFileDlg
VirtualFilter=dWC

[DLG:IDD_XCC_OBJECT_EXTRACTOR]
Type=1
Class=CXCCObjectExtractorDlg
ControlCount=11
Control1=IDOK,button,1342242816
Control2=IDC_LIST,SysListView32,1350631435
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_NAME,edit,1350631552
Control8=IDC_MAIL,edit,1350631552
Control9=IDC_LINK_TITLE,edit,1350631552
Control10=IDC_LINK,edit,1350631552
Control11=IDC_EXTRACT,button,1342242817

[CLS:CXCCObjectExtractorDlg]
Type=0
HeaderFile=XCCObjectExtractorDlg.h
ImplementationFile=XCCObjectExtractorDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CXCCObjectExtractorDlg
VirtualFilter=dWC

[DLG:IDD_XSTE]
Type=1
Class=CXSTE_dlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,SysListView32,1350664713
Control4=IDC_EDIT,button,1476460544
Control5=IDC_INSERT,button,1342242816
Control6=IDC_DELETE,button,1476460544

[CLS:CXSTE_dlg]
Type=0
HeaderFile=XSTE_dlg.h
ImplementationFile=XSTE_dlg.cpp
BaseClass=ETSLayoutDialog
Filter=D
LastObject=CXSTE_dlg
VirtualFilter=dWC

[DLG:IDD_XSTE_EDIT]
Type=1
Class=CXSTE_edit_dlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,edit,1350633600
Control4=IDC_VALUE,edit,1350635588
Control5=IDC_EXTRA_VALUE,edit,1350631552

[CLS:CXSTE_edit_dlg]
Type=0
HeaderFile=XSTE_edit_dlg.h
ImplementationFile=XSTE_edit_dlg.cpp
BaseClass=ETSLayoutDialog
Filter=D
LastObject=CXSTE_edit_dlg
VirtualFilter=dWC

[DLG:IDD_XSE]
Type=1
Class=CXSE_dlg
ControlCount=10
Control1=IDC_LIST,SysListView32,1350631433
Control2=IDC_PLAY,button,1476460544
Control3=IDC_EXTRACT,button,1476460544
Control4=IDC_DELETE,button,1476460544
Control5=IDC_COMPACT,button,1476460544
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_EXTRACT_TO_EDIT,edit,1350631552
Control9=IDC_EXTRACT_TO_STATIC,static,1342308352
Control10=IDC_EXTRACT_TO_BUTTON,button,1342242816

[CLS:CXSE_dlg]
Type=0
HeaderFile=XSE_dlg.h
ImplementationFile=XSE_dlg.cpp
BaseClass=ETSLayoutDialog
Filter=C
LastObject=IDC_EXTRACT_TO_BUTTON
VirtualFilter=dWC

[CLS:CXSE_list]
Type=0
HeaderFile=XSE_list.h
ImplementationFile=XSE_list.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC


; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=Cdlg_new_container
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "xcc mixer.h"
LastPage=0

ClassCount=17
Class1=CDirectoriesDlg
Class2=Cdlg_new_container
Class3=Cdlg_shp_viewer
Class4=CMainFrame
Class5=CResizeDlg
Class6=CSearchFileDlg
Class7=CSelectPaletDlg
Class8=Cshp_properties_dlg
Class9=CXCCMixerApp
Class10=CXCCMixerDoc
Class11=CXCCMixerView
Class12=CXCCFileView
Class13=CXCCObjectExtractorDlg
Class14=CXSE_dlg
Class15=CXSE_list
Class16=CXSTE_dlg
Class17=CXSTE_edit_dlg

ResourceCount=13
Resource1=IDD_SELECT_PALET
Resource2=CG_IDR_POPUP_MIX_VIEW (English (U.S.))
Resource3=IDR_MAINFRAME (English (U.S.))
Resource4=IDD_DIRECTORIES (English (U.S.))
Resource5=IDD_RESIZE (English (U.S.))
Resource6=IDD_SEARCH_FILE (English (U.S.))
Resource7=IDD_XCC_OBJECT_EXTRACTOR (English (U.S.))
Resource8=IDD_XSTE (English (U.S.))
Resource9=IDD_XSTE_EDIT (English (U.S.))
Resource10=IDD_XSE (English (U.S.))
Resource11=IDD_SHP_PROPERTIES (English (U.S.))
Resource12=IDD_SHP_VIEWER (English (U.S.))
Resource13=IDD_NEW_CONTAINER (English (U.S.))

[CLS:CDirectoriesDlg]
Type=0
BaseClass=CDialog
HeaderFile=DirectoriesDlg.h
ImplementationFile=DirectoriesDlg.cpp
LastObject=CDirectoriesDlg

[CLS:Cdlg_new_container]
Type=0
BaseClass=CDialog
HeaderFile=dlg_new_container.h
ImplementationFile=dlg_new_container.cpp
Filter=D
VirtualFilter=dWC

[CLS:Cdlg_shp_viewer]
Type=0
BaseClass=ETSLayoutDialog
HeaderFile=dlg_shp_viewer.h
ImplementationFile=dlg_shp_viewer.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CResizeDlg]
Type=0
BaseClass=CDialog
HeaderFile=ResizeDlg.h
ImplementationFile=ResizeDlg.cpp

[CLS:CSearchFileDlg]
Type=0
BaseClass=ETSLayoutDialog
HeaderFile=SearchFileDlg.h
ImplementationFile=SearchFileDlg.cpp

[CLS:CSelectPaletDlg]
Type=0
BaseClass=ETSLayoutDialog
HeaderFile=SelectPaletDlg.h
ImplementationFile=SelectPaletDlg.cpp

[CLS:Cshp_properties_dlg]
Type=0
BaseClass=CDialog
HeaderFile=shp_properties_dlg.h
ImplementationFile=shp_properties_dlg.cpp

[CLS:CXCCMixerApp]
Type=0
BaseClass=CWinApp
HeaderFile=XCC Mixer.h
ImplementationFile=XCC Mixer.cpp

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

[CLS:CXCCFileView]
Type=0
BaseClass=CScrollView
HeaderFile=XCCFileView.h
ImplementationFile=XCCFileView.cpp

[CLS:CXCCObjectExtractorDlg]
Type=0
BaseClass=ETSLayoutDialog
HeaderFile=XCCObjectExtractorDlg.h
ImplementationFile=XCCObjectExtractorDlg.cpp

[CLS:CXSE_dlg]
Type=0
BaseClass=ETSLayoutDialog
HeaderFile=XSE_dlg.h
ImplementationFile=XSE_dlg.cpp

[CLS:CXSE_list]
Type=0
BaseClass=CListCtrl
HeaderFile=XSE_list.h
ImplementationFile=XSE_list.cpp

[CLS:CXSTE_dlg]
Type=0
BaseClass=ETSLayoutDialog
HeaderFile=XSTE_dlg.h
ImplementationFile=XSTE_dlg.cpp

[CLS:CXSTE_edit_dlg]
Type=0
BaseClass=ETSLayoutDialog
HeaderFile=XSTE_edit_dlg.h
ImplementationFile=XSTE_edit_dlg.cpp

[DLG:IDD_DIRECTORIES]
Type=1
Class=CDirectoriesDlg

[DLG:IDD_NEW_CONTAINER]
Type=1
Class=Cdlg_new_container

[DLG:IDD_SHP_VIEWER]
Type=1
Class=Cdlg_shp_viewer

[DLG:IDD_RESIZE]
Type=1
Class=CResizeDlg

[DLG:IDD_SEARCH_FILE]
Type=1
Class=CSearchFileDlg

[DLG:IDD_SELECT_PALET]
Type=1
Class=CSelectPaletDlg
ControlCount=4
Control1=IDC_LIST,SysListView32,1350647821
Control2=IDOK,button,1476460545
Control3=IDCANCEL,button,1342242816
Control4=IDC_TREE,SysTreeView32,1350636583

[DLG:IDD_SHP_PROPERTIES]
Type=1
Class=Cshp_properties_dlg

[DLG:IDD_XCC_OBJECT_EXTRACTOR]
Type=1
Class=CXCCObjectExtractorDlg

[DLG:IDD_XSE]
Type=1
Class=CXSE_dlg

[DLG:IDD_XSTE]
Type=1
Class=CXSTE_dlg

[DLG:IDD_XSTE_EDIT]
Type=1
Class=CXSTE_edit_dlg

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_CREATE_SFL
Command5=ID_FILE_SEARCH
Command6=ID_FILE_FOUND_UPDATE
Command7=ID_APP_EXIT
Command8=ID_CONVERSION_COMBINE_SHADOWS
Command9=ID_CONVERSION_ENABLE_COMPRESSION
Command10=ID_CONVERSION_SPLIT_SHADOWS
Command11=ID_VIEW_GAME_TD
Command12=ID_VIEW_GAME_RA
Command13=ID_VIEW_GAME_TS
Command14=ID_VIEW_GAME_AUTO
Command15=ID_VIEW_PALET_UPDATE
Command16=ID_VIEW_PALET_AUTO
Command17=ID_VIEW_PALET_AUTO_SELECT
Command18=ID_VIEW_PALET_SELECT
Command19=ID_VIEW_PALET_PREV
Command20=ID_VIEW_PALET_NEXT
Command21=ID_VIEW_PALET_CONVERT_FROM_TD
Command22=ID_VIEW_PALET_CONVERT_FROM_RA
Command23=ID_VIEW_PALET_USE_FOR_CONVERSION
Command24=ID_VIEW_VOXEL_NORMAL
Command25=ID_VIEW_VOXEL_SURFACE_NORMALS
Command26=ID_VIEW_VOXEL_DEPTH_INFORMATION
Command27=ID_VIEW_DIRECTX_OPTIONS
Command28=ID_VIEW_DIRECTORIES
Command29=ID_VIEW_REPORT
Command30=ID_INTERNET_FS_SITE
Command31=ID_INTERNET_SE_SITE
Command32=ID_INTERNET_XCC_SITE
Command33=ID_UTILITIES_XCC_AV_PLAYER
Command34=ID_UTILITIES_XCC_EDITOR
Command35=ID_UTILITIES_XCC_MIX_EDITOR
Command36=ID_LAUNCH_XMC
Command37=ID_LAUNCH_XML
Command38=ID_LAUNCH_XOE_TS
Command39=ID_LAUNCH_XOE_RA2
Command40=ID_LAUNCH_XSE
Command41=ID_LAUNCH_XSTE_RA2
Command42=ID_LAUNCH_XSTE_RA2_YR
Command43=ID_LAUNCH_XSTE_GR
Command44=ID_LAUNCH_XTW_TS
Command45=ID_LAUNCH_XTW_RA2
Command46=ID_LAUNCH_XTW_RA2_YR
Command47=ID_UTILITIES_FS
Command48=ID_LAUNCH_FA
Command49=ID_UTILITIES_SE
Command50=ID_UTILITIES_SEMM
Command51=ID_LAUNCH_RAGE
Command52=ID_LAUNCH_DUNE2
Command53=ID_LAUNCH_TD
Command54=ID_LAUNCH_RA
Command55=ID_LAUNCH_DUNE2000
Command56=ID_LAUNCH_TS
Command57=ID_LAUNCH_RA2
CommandCount=57

[MNU:CG_IDR_POPUP_MIX_VIEW (English (U.S.))]
Type=1
Class=?
Command1=ID_POPUP_OPEN
Command2=ID_POPUP_OPEN_WITH_FINALSUN
Command3=ID_POPUP_OPEN_WITH_FINALALERT
Command4=ID_POPUP_EXPLORE
Command5=ID_POPUP_CLIPBOARD_COPY
Command6=ID_POPUP_CLIPBOARD_PASTE_AS_JPEG
Command7=ID_POPUP_CLIPBOARD_PASTE_AS_PCX
Command8=ID_POPUP_CLIPBOARD_PASTE_AS_PNG
Command9=ID_POPUP_CLIPBOARD_PASTE_AS_SHP_TS
Command10=ID_POPUP_EXTRACT
Command11=ID_POPUP_COPY
Command12=ID_POPUP_COPY_AS_AUD
Command13=ID_POPUP_COPY_AS_AVI
Command14=ID_POPUP_COPY_AS_CPS
Command15=ID_POPUP_COPY_AS_CSV
Command16=ID_POPUP_COPY_AS_HTML
Command17=ID_POPUP_COPY_AS_HVA
Command18=ID_POPUP_COPY_AS_JPEG
Command19=ID_POPUP_COPY_AS_MAP_TS_PREVIEW
Command20=ID_POPUP_COPY_AS_PAL
Command21=ID_POPUP_COPY_AS_PAL_JASC
Command22=ID_POPUP_COPY_AS_PCX_SINGLE
Command23=ID_POPUP_COPY_AS_PCX
Command24=ID_POPUP_COPY_AS_PNG_SINGLE
Command25=ID_POPUP_COPY_AS_PNG
Command26=ID_POPUP_COPY_AS_SHP
Command27=ID_POPUP_COPY_AS_SHP_TS
Command28=ID_POPUP_COPY_AS_TGA
Command29=ID_POPUP_COPY_AS_TEXT
Command30=ID_POPUP_COPY_AS_TMP_TS
Command31=ID_POPUP_COPY_AS_VXL
Command32=ID_POPUP_COPY_AS_WAV_IMA_ADPCM
Command33=ID_POPUP_COPY_AS_WAV_PCM
Command34=ID_POPUP_COPY_AS_WSA
Command35=ID_POPUP_COPY_AS_XIF
Command36=ID_POPUP_IMPORT_INTO_TS
Command37=ID_POPUP_IMPORT_INTO_RA2
Command38=ID_POPUP_REFRESH
Command39=ID_POPUP_RESIZE
Command40=ID_POPUP_COMPACT
Command41=ID_POPUP_DELETE
CommandCount=41

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_VIEW_PALET_PREV
Command2=ID_VIEW_PALET_NEXT
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SEARCH
Command5=ID_FILE_NEW
Command6=ID_FILE_OPEN
Command7=ID_VIEW_PALET_SELECT
Command8=ID_VIEW_PALET_AUTO_SELECT
Command9=ID_POPUP_DELETE
Command10=ID_POPUP_DELETE
Command11=ID_POPUP_REFRESH
Command12=ID_POPUP_OPEN
CommandCount=12

[DLG:IDD_DIRECTORIES (English (U.S.))]
Type=1
Class=?
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

[DLG:IDD_RESIZE (English (U.S.))]
Type=1
Class=?
ControlCount=13
Control1=IDC_RELATIVE_CX,edit,1350639744
Control2=IDC_RELATIVE_CY,edit,1350639744
Control3=IDC_MAINTAIN_ASPECT_RATIO,button,1342242819
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_CX,edit,1350639744
Control7=IDC_CY,edit,1350639744
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,button,1342177287

[DLG:IDD_SEARCH_FILE (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_FILENAME,edit,1350631552
Control2=IDC_LIST,SysListView32,1350647821
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_FILENAME_STATIC,static,1342308352

[DLG:IDD_XCC_OBJECT_EXTRACTOR (English (U.S.))]
Type=1
Class=?
ControlCount=14
Control1=IDOK,button,1342242816
Control2=IDC_LIST,SysListView32,1350631435
Control3=IDC_NAME_STATIC,static,1342308352
Control4=IDC_MAIL_STATIC,static,1342308352
Control5=IDC_LINK_STATIC,static,1342308352
Control6=IDC_LINK_TITLE_STATIC,static,1342308352
Control7=IDC_NAME,edit,1350631552
Control8=IDC_MAIL,edit,1350631552
Control9=IDC_LINK_TITLE,edit,1350631552
Control10=IDC_LINK,edit,1350631552
Control11=IDC_EXTRACT,button,1342242817
Control12=IDC_EXTRACT_TO_STATIC,static,1342308352
Control13=IDC_EXTRACT_TO_EDIT,edit,1350631552
Control14=IDC_EXTRACT_TO_BUTTON,button,1342242816

[DLG:IDD_XSTE (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST,SysListView32,1350631945
Control4=IDC_EDIT,button,1476460545
Control5=IDC_INSERT,button,1342242816
Control6=IDC_DELETE,button,1476460544
Control7=IDC_CAT_LIST,SysListView32,1350664223

[DLG:IDD_XSTE_EDIT (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NAME,edit,1350633600
Control4=IDC_VALUE,edit,1350635588
Control5=IDC_EXTRA_VALUE,edit,1350631552

[DLG:IDD_XSE (English (U.S.))]
Type=1
Class=?
ControlCount=10
Control1=IDC_LIST,SysListView32,1350631433
Control2=IDC_PLAY,button,1342242817
Control3=IDC_EXTRACT,button,1342242816
Control4=IDC_DELETE,button,1342242816
Control5=IDC_COMPACT,button,1342242816
Control6=IDOK,button,1342242816
Control7=IDCANCEL,button,1342242816
Control8=IDC_EXTRACT_TO_EDIT,edit,1350631552
Control9=IDC_EXTRACT_TO_STATIC,static,1342308352
Control10=IDC_EXTRACT_TO_BUTTON,button,1342242816

[DLG:IDD_SHP_PROPERTIES (English (U.S.))]
Type=1
Class=?
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_CX,edit,1350639744
Control6=IDC_CY,edit,1350639744
Control7=IDC_STATIC,static,1342308352
Control8=IDC_C_FRAMES,edit,1350639744

[DLG:IDD_SHP_VIEWER (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_IMAGE,static,1342177806
Control3=IDC_SLIDER,msctls_trackbar32,1342242840
Control4=IDC_FRAME,edit,1350641794

[DLG:IDD_NEW_CONTAINER (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COMBO,combobox,1344339971


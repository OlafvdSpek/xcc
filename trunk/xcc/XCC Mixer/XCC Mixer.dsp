# Microsoft Developer Studio Project File - Name="XCC Mixer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XCC Mixer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XCC Mixer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XCC Mixer.mak" CFG="XCC Mixer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XCC Mixer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XCC Mixer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XCC Mixer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "JPEG_SUPPORT" /D "PNG_SUPPORT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib dsound.lib vfw32.lib libpng.lib libjpeg.lib ogg_static.lib vorbis_static.lib vorbisfile_static.lib bzip_static.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\misc\library"
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "XCC Mixer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\misc" /I "..\..\misc\include" /I "..\misc" /I "..\..\xhp\cgi-bin\misc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "JPEG_SUPPORT" /D "PNG_SUPPORT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ddraw.lib dsound.lib vfw32.lib libpng.lib libjpeg.lib ogg_static.lib vorbis_static.lib vorbisfile_static.lib bzip_static.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\misc\library"
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "XCC Mixer - Win32 Release"
# Name "XCC Mixer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\misc\big_edit.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\big_file_write.cpp
# End Source File
# Begin Source File

SOURCE="..\..\xhp\cgi-bin\misc\cgi.cpp"
# End Source File
# Begin Source File

SOURCE=.\DirectoriesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg_shp_viewer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\ETSLayout.cpp
# End Source File
# Begin Source File

SOURCE="..\..\xhp\cgi-bin\misc\file31.cpp"
# End Source File
# Begin Source File

SOURCE=..\misc\itc_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\log_window.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\map_ts_encoder.cpp
# End Source File
# Begin Source File

SOURCE=.\palet_filter.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pkt_ts_ini_reader.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchStringDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectPaletDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\shp_properties_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\misc\timer.cpp
# End Source File
# Begin Source File

SOURCE="..\..\xhp\cgi-bin\misc\web_tools.cpp"
# End Source File
# Begin Source File

SOURCE=..\misc\xap.cpp
# End Source File
# Begin Source File

SOURCE=".\XCC Mixer.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC Mixer.rc"
# End Source File
# Begin Source File

SOURCE=".\XCC MixerDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC MixerView.cpp"
# End Source File
# Begin Source File

SOURCE=.\XCCFileView.cpp
# End Source File
# Begin Source File

SOURCE=.\XCCObjectExtractorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XSE_dlg.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\XSTE.cpp
# End Source File
# Begin Source File

SOURCE=.\XSTE_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XSTE_edit_dlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\misc\big_edit.h
# End Source File
# Begin Source File

SOURCE=..\misc\big_file_write.h
# End Source File
# Begin Source File

SOURCE=..\misc\cc_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\csf_file.h
# End Source File
# Begin Source File

SOURCE=.\DirectoriesDlg.h
# End Source File
# Begin Source File

SOURCE=.\dlg_shp_viewer.h
# End Source File
# Begin Source File

SOURCE=..\misc\extract_object.h
# End Source File
# Begin Source File

SOURCE=.\fs_ini_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\hva_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\id_log.h
# End Source File
# Begin Source File

SOURCE=..\misc\ima_adpcm_wav_decode.h
# End Source File
# Begin Source File

SOURCE=..\misc\ima_adpcm_wav_encode.h
# End Source File
# Begin Source File

SOURCE=..\misc\image_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\itc_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\jpeg_file.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=..\misc\map_ra_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\map_td_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\map_ts_encoder.h
# End Source File
# Begin Source File

SOURCE=..\misc\map_ts_ini_reader.h
# End Source File
# Begin Source File

SOURCE=..\misc\mix_rg_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\ogg_file.h
# End Source File
# Begin Source File

SOURCE=.\palet_filter.h
# End Source File
# Begin Source File

SOURCE=..\misc\pkt_ts_ini_reader.h
# End Source File
# Begin Source File

SOURCE=.\ResizeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SearchFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\SearchStringDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelectPaletDlg.h
# End Source File
# Begin Source File

SOURCE=.\shp_properties_dlg.h
# End Source File
# Begin Source File

SOURCE=..\misc\st_file.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_file.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_image.h
# End Source File
# Begin Source File

SOURCE="..\..\..\XCC Home Page\cgi-bin\misc\web_tools.h"
# End Source File
# Begin Source File

SOURCE=".\XCC Mixer.h"
# End Source File
# Begin Source File

SOURCE=".\XCC MixerDoc.h"
# End Source File
# Begin Source File

SOURCE=".\XCC MixerView.h"
# End Source File
# Begin Source File

SOURCE=.\XCCFileView.h
# End Source File
# Begin Source File

SOURCE=.\XCCObjectExtractorDlg.h
# End Source File
# Begin Source File

SOURCE=.\xm_types.h
# End Source File
# Begin Source File

SOURCE=.\XSE_dlg.h
# End Source File
# Begin Source File

SOURCE=..\misc\XSTE.h
# End Source File
# Begin Source File

SOURCE=.\XSTE_dlg.h
# End Source File
# Begin Source File

SOURCE=.\XSTE_edit_dlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\XCC Mixer.ico"
# End Source File
# Begin Source File

SOURCE=".\res\XCC Mixer.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\XCC MixerDoc.ico"
# End Source File
# End Group
# End Target
# End Project
# Section XCC Mixer : {72ADFD6C-2C39-11D0-9903-00A0C91BC942}
# 	1:21:CG_IDR_POPUP_MIX_VIEW:102
# End Section

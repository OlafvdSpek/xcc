# Microsoft Developer Studio Project File - Name="XCC Editor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XCC Editor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XCC Editor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XCC Editor.mak" CFG="XCC Editor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XCC Editor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XCC Editor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XCC Editor - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /Gi /GX /O2 /I "j:\vc\xcc\xcc editor" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ddraw.lib dsound.lib vfw32.lib libpng.lib libjpeg.lib ogg_static.lib vorbis_static.lib vorbisfile_static.lib bzip_static.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "XCC Editor - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /ZI /Od /I "j:\vc\xcc\xcc editor" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x413 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ddraw.lib dsound.lib vfw32.lib libpng.lib libjpeg.lib ogg_static.lib vorbis_static.lib vorbisfile_static.lib bzip_static.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "XCC Editor - Win32 Release"
# Name "XCC Editor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\edit_basic_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_briefing_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_infantry_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_infantry_properties_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_map_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_side_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_structure_properties_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_structures_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_teamtype_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_teamtypes_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_trigger_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_triggers_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_unit_properties_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_units_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_waypoints_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\energy_status_dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\list_ctrl_extension.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\log_window.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\object_selection.cpp
# End Source File
# Begin Source File

SOURCE=.\open_from_mix_dlg.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\shp_images.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\misc\timer.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_tfile_write.cpp
# End Source File
# Begin Source File

SOURCE=".\XCC Editor.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC Editor.rc"
# End Source File
# Begin Source File

SOURCE=".\XCC EditorDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\XCC EditorView.cpp"
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_cell_manager.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_infantry.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_level.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_log.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_mixs.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_overlays.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_registry.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_structures.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_templates.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_units.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\edit_infantry_properties_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_structure_properties_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_teamtype_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_teamtypes_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_trigger_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_triggers_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_unit_properties_dlg.h
# End Source File
# Begin Source File

SOURCE=.\edit_waypoints_dlg.h
# End Source File
# Begin Source File

SOURCE=.\energy_status_dlg.h
# End Source File
# Begin Source File

SOURCE=.\infantry_properties_dlg.h
# End Source File
# Begin Source File

SOURCE=.\list_ctrl_extension.h
# End Source File
# Begin Source File

SOURCE=..\misc\log_window.h
# End Source File
# Begin Source File

SOURCE=.\log_window.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\object_selection.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\misc\virtual_tfile_write.h
# End Source File
# Begin Source File

SOURCE=".\XCC Editor.h"
# End Source File
# Begin Source File

SOURCE=".\XCC EditorDoc.h"
# End Source File
# Begin Source File

SOURCE=".\XCC EditorView.h"
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_level.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=".\res\XCC Editor.ico"
# End Source File
# Begin Source File

SOURCE=".\res\XCC Editor.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\XCC EditorDoc.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\XCC Editor.reg"
# End Source File
# End Target
# End Project
# Section XCC Editor : {73746E65-535C-6C70-6173-682073637265}
# 	1:32:CG_IDR_POPUP_CTEMPLATE_SELECTION:105
# End Section
# Section XCC Editor : {72642D72-7761-6C20-6973-74626F782061}
# 	1:27:CG_IDR_POPUP_XCCEDITOR_VIEW:102
# End Section

# Microsoft Developer Studio Project File - Name="Compile mdfs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Compile mdfs - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Compile mdfs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Compile mdfs.mak" CFG="Compile mdfs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Compile mdfs - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Compile mdfs - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Compile mdfs - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\misc" /I "..\misc" /I "..\..\misc\zlib" /I "..\..\misc\libpng" /I "..\..\xhp\cgi-bin\misc" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "NO_FT_SUPPORT" /YX /FD /c
# ADD BASE RSC /l 0x413 /d "NDEBUG"
# ADD RSC /l 0x413 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Compile mdfs - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\misc" /I "..\misc" /I "..\..\misc\zlib" /I "..\..\misc\libpng" /I "..\..\xhp\cgi-bin\misc" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "NO_FT_SUPPORT" /YX /FD /c
# ADD BASE RSC /l 0x413 /d "_DEBUG"
# ADD RSC /l 0x413 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Compile mdfs - Win32 Release"
# Name "Compile mdfs - Win32 Debug"
# Begin Source File

SOURCE=..\..\misc\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\cc_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\crc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\ddpf_conversion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\file32.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\file32.h
# End Source File
# Begin Source File

SOURCE=..\..\misc\fname.cpp
# End Source File
# Begin Source File

SOURCE=.\fname.h
# End Source File
# Begin Source File

SOURCE=..\misc\id_log.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_cache.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\mix_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\multi_line.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\multi_line.h
# End Source File
# Begin Source File

SOURCE=..\misc\pak_file.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\palet.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pcx_decode.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\pcx_file_write.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\string_conversion.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_dirs.cpp
# End Source File
# Begin Source File

SOURCE=..\misc\xcc_registry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\misc\xstring.cpp
# End Source File
# End Target
# End Project

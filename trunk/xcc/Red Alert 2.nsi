!define VERSION "0.0.0"

Name "Red Alert 2 ${VERSION}"
Outfile "Red_Alert-2-${VERSION}.exe"
InstallDir "$PROGRAMFILES\Red Alert 2"
InstallDirRegKey HKLM "Software\Westwood\Red Alert 2" "InstallDir"
Page directory
Page instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"

	File /r "Red Alert 2\*"
	Exec 'regsvr32 /s "$INSTDIR\wolapi"'
	CreateShortCut "$SMPROGRAMS\Red Alert 2.lnk" "$INSTDIR\Game.exe"
	WriteRegStr HKLM "Software\Westwood\Red Alert 2" "InstallDir" "$INSTDIR"
	#WriteRegStr HKLM "Software\Westwood\Red Alert 2" "InstallPath" "$INSTDIR\Game.exe"
	#WriteRegStr HKLM "Software\Westwood\Red Alert 2" "Serial" ""
	WriteRegStr HKLM "Software\Westwood\WOLAPI" "InstallPath" "$INSTDIR\WOLAPI.DLL"
SectionEnd

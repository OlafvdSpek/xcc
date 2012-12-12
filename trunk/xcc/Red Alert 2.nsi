Name "Red Alert 2"
Outfile "Red-Alert-2-Multiplayer.exe"
InstallDir "$PROGRAMFILES\Red Alert 2"
XPStyle on
Page directory
Page instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"

	File /r "rmcache"
	File /r "taunts"
	File "binkw32.dll"
	File "blowfish.dll"
	File "language.mix"
	File "maps01.mix"
	File "movies01.mix"
	File "mph.exe"
	File "multi.mix"
	File "nl.cfg"
	File "ra2.mix"
	File "red alert 2.exe"
	File "theme.mix"
	File "wolapi.dll"
	File "wolapi.war"
	File "xwis.dll"
	Exec 'regsvr32 /s "$INSTDIR\wolapi"'
	CreateShortCut "$SMPROGRAMS\Red Alert 2.lnk" "$INSTDIR\Red Alert 2.exe"
	WriteRegStr HKLM "Software\Westwood\Red Alert 2" "InstallPath" "$INSTDIR\Red Alert 2.exe"
	WriteRegStr HKLM "Software\Westwood\WOLAPI" "InstallPath" "$INSTDIR\wolapi.dll"
SectionEnd

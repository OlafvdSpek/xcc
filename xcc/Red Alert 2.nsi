!define VERSION "0.0.1"

Name "Red Alert 2 ${VERSION}"
Outfile "Red_Alert-2-${VERSION}.exe"
InstallDir "$PROGRAMFILES\Red Alert 2"
InstallDirRegKey HKLM "Software\Westwood\Red Alert 2" "InstallDir"
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
	File "conquer.dat"
	File "game.exe"
	File "language.mix"
	File "maps01.mix"
	File "movies01.mix"
	File "mph.exe"
	File "multi.mix"
	File "nl.cfg"
	File "ra2.exe"
	File "ra2.mix"
	File "theme.mix"
	File "wolapi.dll"
	File "wolapi.war"
	Exec 'regsvr32 /s "$INSTDIR\wolapi"'
	CreateShortCut "$SMPROGRAMS\Red Alert 2.lnk" "$INSTDIR\Game.exe"
	WriteRegStr HKLM "Software\Westwood\Red Alert 2" "InstallDir" "$INSTDIR"
	WriteRegStr HKLM "Software\Westwood\Red Alert 2" "InstallPath" "$INSTDIR\Game.exe"
	WriteRegStr HKLM "Software\Westwood\WOLAPI" "InstallPath" "$INSTDIR\wolapi.dll"
SectionEnd

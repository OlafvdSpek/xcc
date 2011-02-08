!define VERSION "0.0.1"

Name "Tiberian Sun ${VERSION}"
Outfile "Tiberian_Sun-${VERSION}.exe"
InstallDir "$PROGRAMFILES\Tiberian Sun"
InstallDirRegKey HKLM "Software\Westwood\Tiberian Sun" "InstallDir"
XPStyle on
Page directory
Page instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"

	File "blowfish.dll"
	File "game.exe"
	File "language.dll"
	File "multi.mix"
	File "sidecd01.mix"
	File "sidecd02.mix"
	File "tibsun.mix"
	File "nl.cfg"
	File "wolapi.dll"
	File "wolapi.war"
	Exec 'regsvr32 /s "$INSTDIR\wolapi"'
	CreateShortCut "$SMPROGRAMS\Tiberian Sun.lnk" "$INSTDIR\Game.exe"
	WriteRegStr HKLM "Software\Westwood\Tiberian Sun" "InstallDir" "$INSTDIR"
	WriteRegStr HKLM "Software\Westwood\Tiberian Sun" "InstallPath" "$INSTDIR\Game.exe"
	WriteRegStr HKLM "Software\Westwood\WOLAPI" "InstallPath" "$INSTDIR\wolapi.dll"
SectionEnd

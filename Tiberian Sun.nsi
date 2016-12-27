Name "Tiberian Sun"
Outfile "Tiberian-Sun-Multiplayer.exe"
InstallDir "$PROGRAMFILES\Tiberian Sun"
XPStyle on
Page directory
Page instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"

	File "blowfish.dll"
	File "language.dll"
	File "multi.mix"
	File "patch.mix"
	File "sidecd01.mix"
	File "sidecd02.mix"
	File "tiberian sun.exe"
	File "tibsun.mix"
	File "xts.dll"
	File "nl.cfg"
	File "wolapi.dll"
	File "wolapi.war"
	Exec 'regsvr32 /s "$INSTDIR\wolapi"'
	CreateShortCut "$SMPROGRAMS\Tiberian Sun.lnk" "$INSTDIR\Tiberian Sun.exe"
	WriteRegStr HKLM "Software\Westwood\Tiberian Sun" "InstallPath" "$INSTDIR\Tiberian Sun.exe"
	WriteRegStr HKLM "Software\Westwood\WOLAPI" "InstallPath" "$INSTDIR\wolapi.dll"
SectionEnd

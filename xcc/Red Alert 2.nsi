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
	File /oname=game.exe "red alert 2.exe"
	File /oname=ra2.exe "red alert 2.exe"
	File "red alert 2.exe"
	File "theme.mix"
	File "wolapi.dll"
	File "wolapi.war"
	File "xwis.dll"
	Exec 'regsvr32 /s "$INSTDIR\wolapi"'
	CreateShortCut "$SMPROGRAMS\Red Alert 2.lnk" "$INSTDIR\Red Alert 2.exe"
	CreateShortCut "$SMPROGRAMS\Red Alert 2 in a Window.lnk" "$INSTDIR\Red Alert 2.exe" "-win"
	WriteRegStr HKLM "Software\Westwood\Red Alert 2" "InstallPath" "$INSTDIR\Red Alert 2.exe"
	WriteRegStr HKLM "Software\Westwood\WOLAPI" "InstallPath" "$INSTDIR\wolapi.dll"
	WriteRegStr HKCU "Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "$INSTDIR\Red Alert 2.exe" "RUNASADMIN"
	SetRegView 64
	WriteRegStr HKLM "Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "$INSTDIR\Red Alert 2.exe" "RUNASADMIN"
	Exec "$INSTDIR\Red Alert 2.exe"
SectionEnd

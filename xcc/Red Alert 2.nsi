Name "Red Alert 2"
Outfile "Red-Alert-2-Multiplayer.exe"
InstallDir "$DOCUMENTS\Red Alert 2"
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
	File "xwis.cache"
	File "xwis.dll"
	Exec 'regsvr32 /s "$INSTDIR\wolapi"'
	CreateShortCut "$SMPROGRAMS\Red Alert 2.lnk" "$INSTDIR\Game.exe"
	CreateShortCut "$SMPROGRAMS\Red Alert 2 in a Window.lnk" "$INSTDIR\Game.exe" "-win"
	WriteRegStr HKLM "Software\Westwood\Red Alert 2" "InstallPath" "$INSTDIR\Game.exe"
	WriteRegStr HKLM "Software\Westwood\WOLAPI" "InstallPath" "$INSTDIR\wolapi.dll"
	WriteRegStr HKCU "Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "$INSTDIR\Game.exe" "HIGHDPIAWARE RUNASADMIN WIN7RTM"
	WriteRegStr HKCU "Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "$INSTDIR\Red Alert 2.exe" "HIGHDPIAWARE RUNASADMIN WIN7RTM"
	SetRegView 64
	WriteRegStr HKLM "Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "$INSTDIR\Game.exe" "HIGHDPIAWARE RUNASADMIN WIN7RTM"
	WriteRegStr HKLM "Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "$INSTDIR\Red Alert 2.exe" "HIGHDPIAWARE RUNASADMIN WIN7RTM"
	Exec "$INSTDIR\Game.exe"
	Quit

	; 16BITCOLOR
SectionEnd

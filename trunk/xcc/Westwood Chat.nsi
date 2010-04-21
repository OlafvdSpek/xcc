!define VERSION "4.221"

Name "Westwood Chat ${VERSION}"
Outfile "Westwood_Chat-${VERSION}.exe"
InstallDir "$PROGRAMFILES\Westwood Chat"
InstallDirRegKey HKLM "Software\Westwood\WChat" "InstallPath"
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section "Install"
	SetShellVarContext all
	SetOutPath "$INSTDIR"
	WriteUninstaller "$INSTDIR\Uninstall.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Westwood Chat" "DisplayName" "Westwood Chat ${VERSION}"
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Westwood Chat" "NoModify" 1
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Westwood Chat" "UninstallString" '"$INSTDIR\Uninstall.exe"'
	WriteRegStr HKLM "Software\Westwood\WChat" "Name" ""
	WriteRegStr HKLM "Software\Westwood\WChat" "InstallPath" "$INSTDIR\WChat.exe"
	WriteRegDWORD HKLM "Software\Westwood\WChat" "SKU" 1000
	WriteRegDWORD HKLM "Software\Westwood\WChat" "Version" 262365
	File bcast16.wav
	File bcast8.wav
	File deisl1.isu
	File deisl2.isu
	File enable16.wav
	File enable8.wav
	File invite16.wav
	File invite8.wav
	File kick16.wav
	File kick8.wav
	File license.txt
	File nl.cfg
	File pager16.wav
	File pager8.wav
	File patchw32.dll
	File register.exe
	File thanks16.wav
	File thanks8.wav
	File wchat.dat
	File wchat.exe
	File wchat.gid
	File wchat.hlp
	File wchat.pbk
	File wchat.url
	File wchatcc.hlp
	File wchatra.hlp
	File welcom16.wav
	File welcom8.wav
	File westwood.url
	File wupdate.exe
	CreateShortCut "$SMPROGRAMS\Westwood Chat.lnk" "$INSTDIR\WChat.exe"
SectionEnd

Section "Uninstall"
	SetShellVarContext all
	Delete "$SMPROGRAMS\Westwood Chat.lnk"
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Westwood Chat"
	DeleteRegKey HKLM "Software\Westwood\WChat"
	DeleteRegKey /ifempty HKLM "Software\Westwood"
	RMDir /r "$INSTDIR"
SectionEnd

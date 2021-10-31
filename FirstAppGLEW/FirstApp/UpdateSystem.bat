@setlocal enableextensions
@cd /d "%~dp0"
echo off
echo Copying Header Files
echo ----------------------------
copy *.h "C:\Program Files (x86)\Windows Kits\8.1\Include\um\gl"
copy *.h "C:\Program Files (x86)\Windows Kits\8.0\Include\um\gl"
copy *.h "C:\Program Files (x86)\Windows Kits\10\Include\10.0.15063.0\um\gl"
echo Copying Lib Files
echo ----------------------------
copy *.lib "C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x86"
copy *.lib "C:\Program Files (x86)\Windows Kits\8.0\Lib\win8\um\x86"
copy *.lib "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.15063.0\um\x86"
echo Copying DLL Files to SysWOW64
echo ----------------------------
copy *.dll "C:\Windows\SysWOW64"
echo Copying DLL Files to System32
echo ----------------------------
copy *.dll "C:\Windows\System32"
pause

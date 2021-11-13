@echo off

if _%1_==_payload_  goto :payload

:getadmin
    echo %~nx0: elevating self
    set vbs=%temp%\getadmin.vbs
    echo Set UAC = CreateObject^("Shell.Application"^)                >> "%vbs%"
    echo UAC.ShellExecute "%~s0", "payload %~sdp0 %*", "", "runas", 1 >> "%vbs%"
    "%temp%\getadmin.vbs"
    del "%temp%\getadmin.vbs"
goto :eof

:payload

START wsl.exe -d Ubuntu-20.04 "/mnt/c/Nonprograms/Anul3/Sem2/IP/SmartWindow/server.sh"
timeout /t 50
START wsl.exe -d Ubuntu-20.04 "/mnt/c/Nonprograms/Anul3/Sem2/IP/SmartWindow/req.sh"

echo.
echo...Script Complete....
echo.

pause

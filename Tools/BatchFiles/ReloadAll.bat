@echo off

taskkill /F /IM DayZDiag_x64.exe

timeout /t 1 /nobreak

::TODO call build bat

::Server name
set serverName=GunGameServer
::Server files location
set serverLocation="E:\GameLaunchers\Steam\steamapps\common\DayZServer"
::Server Port
set serverPort=2302
::Server config
set serverConfig=E:\DAYZ\GunGame\Tools\serverDZ.cfg
::Logical CPU cores to use (Equal or less than available)
set serverCPU=2
::DayZServer location (DONT edit)
::cd "%serverLocation%"
echo (%time%) %serverName% started.
::Launch parameters (edit end: -config=|-port=|-profiles=|-doLogs|-adminLog|-netLog|-freezeCheck|-filePatching|-BEpath=|-cpuCount=)
start "DayZ Server" "E:\GameLaunchers\Steam\steamapps\common\DayZServer\DayZDiag_x64" -config=%serverConfig% -port=%serverPort% -cpuCount=%serverCPU% -server -filePatching -mission=P:\GunGame\GunGame.chernarusplus -mod=P:\GunGame\@GunGame; 

timeout /t 3 /nobreak

::Launch parameters (edit end: -config=|-port=|-profiles=|-doLogs|-adminLog|-netLog|-freezeCheck|-filePatching|-BEpath=|-cpuCount=)
start "DayZ Client" /min "C:\Program Files (x86)\SteamGames\steamapps\common\DayZ\DayZDiag_x64" -filePatching -window -mod=P:\GunGame\@GunGame; -connect=localhost -port=2302

timeout /t 6 /nobreak
call SendKeys.bat "Focus switch" "DayZ Client"

timeout /t 6 /nobreak
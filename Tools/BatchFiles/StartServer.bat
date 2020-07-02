@echo off
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
::Sets title for terminal (DONT edit)
title %serverName% batch
::DayZServer location (DONT edit)
cd "%serverLocation%"
echo (%time%) %serverName% started.
::Launch parameters (edit end: -config=|-port=|-profiles=|-doLogs|-adminLog|-netLog|-freezeCheck|-filePatching|-BEpath=|-cpuCount=)
start "DayZ Server" /min "E:\GameLaunchers\Steam\steamapps\common\DayZServer\DayZDiag_x64" -config=%serverConfig% -port=%serverPort% -cpuCount=%serverCPU% -server -filePatching -mission=P:\GunGame\GunGame.chernarusplus -mod=P:\GunGame\@GunGame; 
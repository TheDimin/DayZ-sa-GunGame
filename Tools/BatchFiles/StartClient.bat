@echo off
::Sets title for terminal (DONT edit)
title %serverName% batch
::Launch parameters (edit end: -config=|-port=|-profiles=|-doLogs|-adminLog|-netLog|-freezeCheck|-filePatching|-BEpath=|-cpuCount=)
start "DayZ Client" /min "C:\Program Files (x86)\SteamGames\steamapps\common\DayZ\DayZDiag_x64" -filePatching -window -mod=P:\GunGame\@GunGame; -connect=localhost -port=2302
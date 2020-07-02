@echo off
::Launch parameters (edit end: -config=|-port=|-profiles=|-doLogs|-adminLog|-netLog|-freezeCheck|-filePatching|-BEpath=|-cpuCount=)
start "AddonBuilder" /WAIT "E:\GameLaunchers\Steam\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe" P:\GunGame\GunGame P:\GunGame\@GunGame\Addons -clear -sign=P:/GunGame/Tools/Keys/TheDiminGunGamePKEY.biprivatekey -include=P:\GunGame\Tools\Backend\Includes.txt


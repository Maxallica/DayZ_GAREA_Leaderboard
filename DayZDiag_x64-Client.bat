taskkill /im DayZDiag_x64-Client.exe /F

@echo off
:start
: :Name for CMD window
set serverName=Testserver Ragequit
: :Server files location
set serverLocation="%cd%"
: :Server Port
set serverPort=2302
: :Server config
set serverConfig=serverDZ.cfg
: :Server profile folder
set serverProfile=profiles
: :Logical CPU cores to use (Equal or less than available)
set serverCPU=16
: :mods (@modName;@anotherModname)
set "mods=!Workshop/@CF;!Workshop/@VPPAdminTools;@GAREA_Leaderboard;"
: :playerName
set playerName=Maxallica

: : START SCRIPT
: :Sets title for terminal (DONT edit)
title %serverName% batch
: : switch to DayZServer location (DONT edit)
cd "%serverLocation%"
echo (%time%) %serverName% started.
: :Launch parameters (edit end: -config-|-port-|-profiles-|-doLogs|-adminLog|-netlog|-freezeCheck|-filePatching|-BEpath-|-cpuCount-)
start DayZDiag_x64-Client.exe -connect=127.0.0.1 -port=%serverPort% -servermod=%serverMods%  -mod=%mods% -name=%playerName% -instanceId=1 -config=%serverConfig% -profiles=%serverProfile% -cpuCount=%serverCPU% -dologs -adminlog -freezecheck -filePatching -newErrorsAreWarnings=1
: :Time in seconds before kill server process (14400 = 4 hours)
:: timeout 14390
:: taskkill /im DayZDiag_x64-Client.exe /F
: :Time in seconds to wait before..
:: timeout
: :Go back to the top and repeat the whole cycle again
:: goto start
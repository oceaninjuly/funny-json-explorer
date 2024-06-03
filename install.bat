@echo off
cd /D %~dp0

echo Building project...
g++ -I./src/ -I./depends/ ./src/main.cpp -o ./release/fje.exe

::获取当前目录
set currentDir=%cd%

::设置要永久加入到path环境变量中的路径
set newPath=%currentDir%\release
set PATH=%PATH%;%newPath%
::添加到环境变量
reg add "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v "Path" /t REG_EXPAND_SZ /d "%PATH%" /f
pause
exit
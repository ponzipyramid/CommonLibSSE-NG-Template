@echo off

set preset="ALL"
if NOT "%1" == "" (
    set preset=%1
)

echo Running preset %preset%

cmake -S . --preset=%preset% 
if %ERRORLEVEL% NEQ 0 exit 1
cmake --build build --config Release
if %ERRORLEVEL% NEQ 0 exit 1

pause
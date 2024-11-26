@echo off

g++ -Wall -Werror src/*.cpp -o a.out

if errorlevel 1 (
    echo Compilation failed.
    pause
    exit /b 1
)

echo Compilation finished.
pause

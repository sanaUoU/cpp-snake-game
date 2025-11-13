@echo off
echo 🪟 Building Windows version...
echo.

REM Check if SFML is installed
if not exist "C:\SFML" (
    echo ❌ SFML not found at C:\SFML
    echo Please download SFML from https://www.sfml-dev.org/download.php
    echo Extract to C:\SFML
    pause
    exit /b 1
)

REM Compile the game
echo 📦 Compiling game...
g++ -std=c++20 main.cpp -o SnakeGame.exe ^
    -IC:\SFML\include ^
    -LC:\SFML\lib ^
    -lsfml-graphics -lsfml-window -lsfml-system ^
    -DSFML_STATIC

if errorlevel 1 (
    echo ❌ Compilation failed
    pause
    exit /b 1
)

REM Create release directory
if not exist "releases\windows" mkdir releases\windows

REM Copy executable
copy SnakeGame.exe releases\windows\

REM Copy SFML DLLs
echo 📚 Copying SFML libraries...
copy C:\SFML\bin\sfml-graphics-3.dll releases\windows\
copy C:\SFML\bin\sfml-window-3.dll releases\windows\
copy C:\SFML\bin\sfml-system-3.dll releases\windows\
copy C:\SFML\bin\openal32.dll releases\windows\

REM Create README
echo Creating README...
(
echo Snake Game - Windows Edition
echo.
echo Double-click SnakeGame.exe to play!
echo.
echo Controls:
echo   Arrow Keys / WASD - Move
echo   Space - Restart after game over
echo.
echo Enjoy!
) > releases\windows\README.txt

echo.
echo ✅ Windows version built successfully!
echo.
echo 📁 Output: releases\windows\
echo.
echo 🎮 Test: cd releases\windows ^&^& SnakeGame.exe
echo.
pause

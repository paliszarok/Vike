@echo off
if exist build\Vike.exe (
del build\Vike.exe
)
g++ src\*.cpp -o build\Vike.exe -Wall -O2 -pthread -L C:\Dev\raylib -lraylib -lopengl32 -lgdi32 -lwinmm
IF %ERRORLEVEL% NEQ 0 (
echo Build failed!
pause
) else (
echo Build completed!
pause
)
@echo off
gcc main.c game_update.c grid.c block.c tiles.c color.c -o tetris.exe -I../../raylib/include -L../../raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
if %errorlevel% neq 0 exit /b %errorlevel%
echo Build OK

set RELEASE_DIR=..\release
if exist "%RELEASE_DIR%" rmdir /s /q "%RELEASE_DIR%"
mkdir "%RELEASE_DIR%"
copy tetris.exe "%RELEASE_DIR%\" >nul
echo Release created: %RELEASE_DIR%\tetris.exe (single-file, %~z0 bytes)

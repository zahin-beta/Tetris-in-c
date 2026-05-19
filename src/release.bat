@echo off
gcc *.c -o tetris.exe -I../raylib/include -L../raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
if %errorlevel% neq 0 exit /b %errorlevel%
echo Build OK

set RELEASE_DIR=..\release
if exist "%RELEASE_DIR%" rmdir /s /q "%RELEASE_DIR%"
mkdir "%RELEASE_DIR%"
copy tetris.exe "%RELEASE_DIR%\" >nul
copy ..\..\raylib\lib\raylib.dll "%RELEASE_DIR%\" >nul
xcopy /e /i ..\assets "%RELEASE_DIR%\assets\" >nul
powershell -Command "Compress-Archive -Path '%RELEASE_DIR%\*' -DestinationPath '%RELEASE_DIR%\tetris-v1.0.zip' -Force"
echo Release created: %RELEASE_DIR%\tetris-v1.0.zip

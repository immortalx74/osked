@echo off

set path=C:\dev\osked;%path%

set SOURCES=imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui-SFML.cpp imgui/imgui_demo.cpp main.cpp
set LINK=lib\sfml-system.lib lib\sfml-graphics.lib lib\sfml-main.lib lib\sfml-window.lib opengl32.lib winmm.lib gdi32.lib lib\freetype.lib

REM DEBUG
set CFLAGS=/MP /EHsc /Zi /FC /nologo /W1 /Od

REM RELEASE
REM set CFLAGS=/MP /EHsc /FC /nologo /W1 /O2

REM set SKIP_WARNINGS=/wd"4838"
set BUILD_DIR=/Fdbuild\ /Fobuild\
set EXE=build/osked.exe

start /wait /B cl %CFLAGS% %BUILD_DIR% /Fe%EXE% /Iinclude %SOURCES% /link %LINK% /SUBSYSTEM:CONSOLE

IF %ERRORLEVEL% EQU 0 start /wait %EXE%
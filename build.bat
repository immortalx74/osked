@echo off

set path=C:\dev\osked;%path%

set SOURCES=imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui-SFML.cpp imgui/imgui_demo.cpp main.cpp

start /wait /B cl /MP /Fdbuild\ /Febuild/osked /Fobuild\  /EHsc /Zi /FC /nologo /W1 /Od /Iinclude /Iimgui %SOURCES% /link lib\sfml-system.lib lib\sfml-graphics.lib lib\sfml-main.lib lib\sfml-window.lib opengl32.lib winmm.lib gdi32.lib lib\freetype.lib

start /wait build/osked.exe
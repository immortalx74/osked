//============================================================================
// - Check if a sample was removed from disk (popup warning? something else?).
// - Calculate correct speed (BPM relationship with rows_per_beat).
// - Possible bug when changing BPM/ticks while on playback. (slows down?)
// - Implement delete/move up/move down for patterns/instruments.
//   What should happen when moving/deleting patterns/instruments?
//   For instruments, should the notes switch to next instrument?
//   What if the instrument with higher index gets removed? 
//   For patterns, there's a lot of data to be moved around.
// - Implement cut/copy/paste. Cursor is always top-left of selection,
//   handle both toolbar and context menu.
// - Bug when playing module. Notes should stop just like when playing
//   a single pattern.
// - Add a "pan" field to notes and include it on PlayRow. It will be set by an FX
// - Prevent sliders (and possibly other ui elements) of having values <>
//   min/max.NOTE:This is an imgui issue.
// - Implement saving/loading application settings. Suggested fields:
//   Default new pattern rows/track count/BPM/Ticks/Middle octave.
//   Window state (pos/size/maximized). Color scheme. Keyb shortcuts.
// - Read/Write file format.
// - WAV export.
// - Right click context menu: Shift note(s) up/down by 1 or by octave,
//   [selection,current track, current pattern, whole module?]
//   Set volume [same as above], Set instrument[same as above]
// - BUG: On module playback mode, stop goes to next pattern. Should stay
//   on same pattern and cursor should be set to row zero.
// - Write ResizePattern. Should be able to grow/shrink the provided pattern
//   and calculate offsets for all other patterns
//============================================================================

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cmath>
#include "imgui.h"
#include "imgui-SFML.h"

#include "portable-file-dialogs.h"

#include <string>
#include <iostream>
#include <array>
#include <Windows.h>
#include "print.cpp"
#include "globals.cpp"
#include "functions.cpp"

#pragma comment (lib, "Comdlg32")
#pragma comment (lib, "OLE32")
#pragma comment (lib, "shell32")

int main()
{
    
	sf::RenderWindow window(sf::VideoMode(1024, 920), "Open Solomon's Key Editor", sf::Style::Default);
	window.setPosition(ImVec2(100,0));
    window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
    sf::Clock deltaClock;
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) window.close();
		}
        
		ImGui::SFML::Update(window, deltaClock.restart());
        //==================================================================
        // TOOLBOX
        
        // layers
        int app_window_height = io.DisplaySize.y;
        int app_window_width = io.DisplaySize.x;
        
        ImGui::SetNextWindowSize(ImVec2(UI.TOOLBOX_WIDTH, app_window_height - (2 * UI.MARGIN)));
        ImGui::SetNextWindowPos(ImVec2(UI.TOOLBOX_X + UI.MARGIN, UI.TOOLBOX_Y + UI.MARGIN));
        ImGui::Begin("toolbox", false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		
        ImGui::PushStyleColor(ImGuiCol_Text, col_title_text);
        ImGui::Text("Layers");
        ImGui::PopStyleColor();
        
        if(ImGui::Checkbox(layer_grid.NAME.c_str(), &layer_grid.VISIBLE))
        {
            //
        }
        
        if(ImGui::Checkbox(layer_blocks.NAME.c_str(), &layer_blocks.VISIBLE))
        {
            //
        }
        
        if(ImGui::Checkbox(layer_enemies.NAME.c_str(), &layer_enemies.VISIBLE))
        {
            //
        }
        
        if(ImGui::Checkbox(layer_items.NAME.c_str(), &layer_items.VISIBLE))
        {
            //
        }
        
        if(ImGui::Checkbox(layer_background.NAME.c_str(), &layer_background.VISIBLE))
        {
            //
        }
        
        // blocks
        
        ImGui::End();
        
        // MAIN
        ImGui::SetNextWindowSize(ImVec2(app_window_width - UI.MAIN_X - UI.MARGIN, app_window_height - (2 * UI.MARGIN)));
        ImGui::SetNextWindowPos(ImVec2(UI.MAIN_X, UI.MAIN_Y));
        ImGui::SetNextWindowContentSize(ImVec2(960 + UI.MARGIN + 4, 768 + UI.MARGIN));
        ImGui::Begin("main", false, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        
        draw_list = ImGui::GetWindowDrawList();
        
        if (layer_grid.VISIBLE)
        {
            DrawGrid();
        }
        
        ImGui::End();
        //=================================================================
        window.clear();
		ImGui::SFML::Render(window);
		window.display();
	}
    
    // shut down
	ImGui::SFML::Shutdown();
    
    //std::cin.get();
}
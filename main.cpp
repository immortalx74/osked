#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

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
    
	sf::RenderWindow window(sf::VideoMode(1250, 800), "Open Solomon's Key Editor", sf::Style::Default);
	window.setPosition(ImVec2(0,0));
    window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
    sf::Clock deltaClock;
	
    LoadTextures();
    InitGrid();
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
		}
        
		ImGui::SFML::Update(window, deltaClock.restart());
        //==================================================================
        // TOOLBOX
        
        int app_window_height = io.DisplaySize.y;
        int app_window_width = io.DisplaySize.x;
        
        
        ImGui::SetNextWindowSize(ImVec2(UI.TOOLBOX_WIDTH, app_window_height - (2 * UI.MARGIN)));
        ImGui::SetNextWindowPos(ImVec2(UI.TOOLBOX_X + UI.MARGIN, UI.TOOLBOX_Y + UI.MARGIN));
        ImGui::Begin("toolbox", false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		
        // file operations
        if (ImGui::SmallButton("New"))
        {
            
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Open"))
        {
            
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Save"))
        {
            
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Save As"))
        {
            
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("About"))
        {
            ImGui::OpenPopup("about");
        }
        
        bool p_about_opened = true;
        if (ImGui::BeginPopupModal("about", &p_about_opened, ImGuiWindowFlags_NoResize))
        {
            ImGui::Text("Open Solomon's Key Editor\nv 1.0 07/2019\nBy Immortalx.\n\nSolomon's Key is a copyright of Tecmo.");
            if (ImGui::Button("OK", ImVec2(80,0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        
        // layers list
        ImGui::PushStyleColor(ImGuiCol_Text, col_title_text);
        ImGui::Text("Layers");
        ImGui::PopStyleColor();
        
        ImGui::Checkbox(layer_grid.NAME.c_str(), &layer_grid.VISIBLE);
        ImGui::Checkbox(layer_blocks.NAME.c_str(), &layer_blocks.VISIBLE);
        ImGui::Checkbox(layer_enemies.NAME.c_str(), &layer_enemies.VISIBLE);
        ImGui::Checkbox(layer_items.NAME.c_str(), &layer_items.VISIBLE);
        ImGui::Checkbox(layer_unique.NAME.c_str(), &layer_unique.VISIBLE);
        ImGui::Checkbox(layer_background.NAME.c_str(), &layer_background.VISIBLE);
        
        // Get current selection from toolbox
        ImVec2 cur_pos = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(UI.TOOLBOX_X + 180, UI.TOOLBOX_Y + 37));
        ImGui::PushStyleColor(ImGuiCol_Text, col_title_text);
        ImGui::Text("Selected");
        ImGui::PopStyleColor();
        ImGui::SetCursorPosX(UI.TOOLBOX_X + 174);
        
        sf::Texture sel_item = GetItemTexture(active_element);
        ImGui::Image(sel_item);
        
        // Switch MODE button
        std::string mode_name;
        if (mode == MODE_PAINT)
        {
            mode_name = " DRAW\n MODE ";
        }
        else
        {
            mode_name = " EDIT\n MODE ";
        }
        ImGui::Spacing();
        ImGui::SetCursorPosX(UI.TOOLBOX_X + 180);
        if (ImGui::Button(mode_name.c_str()))
        {
            if (mode == MODE_PAINT)
            {
                mode = MODE_EDIT;
            }
            else
            {
                mode = MODE_PAINT;
            }
        }
        if(ImGui::IsItemHovered())
        {
            ImGui::SetTooltip("DRAW MODE: Paint selected element on grid with the left mouse button.\nEDIT MODE: Double click an existing element on grid to set its options.");
        }
        ImGui::SetCursorPos(cur_pos);
        
        ImGui::Spacing();
        
        // blocks list
        ImGui::PushStyleColor(ImGuiCol_Text, col_title_text);
        ImGui::Text("Blocks");
        ImGui::PopStyleColor();
        
        if (ImGui::ImageButton(tex_blocks[0], ImVec2(64,64)))
        {
            active_element = BLOCK_VOID;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton(tex_blocks[1], ImVec2(64,64)))
        {
            active_element = BLOCK_REGULAR;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton(tex_blocks[2], ImVec2(64,64)))
        {
            active_element = BLOCK_SOLID;
        }
        
        ImGui::Spacing();
        
        
        //unique list
        ImGui::PushStyleColor(ImGuiCol_Text, col_title_text);
        ImGui::Text("Unique");
        ImGui::PopStyleColor();
        
        if (ImGui::ImageButton(tex_unique[0], ImVec2(64,64)))
        {
            active_element = UNIQUE_PLAYER;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton(tex_unique[1], ImVec2(64,64)))
        {
            active_element = UNIQUE_DOOR;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton(tex_unique[2], ImVec2(64,64)))
        {
            active_element = UNIQUE_KEY;
        }
        
        ImGui::Spacing();
        
        //enemies list
        ImGui::PushStyleColor(ImGuiCol_Text, col_title_text);
        ImGui::Text("Enemies");
        ImGui::PopStyleColor();
        
        if (ImGui::ListBoxHeader("##enemieslist", ImVec2(UI.LIST_WIDTH, UI.LIST_HEIGHT)))
        {   
            for (int i = 0; i < enemies_list.size(); ++i)
            {
                if(ImGui::Selectable(enemies_list[i].c_str(), active_enemy == i))
                {
                    active_enemy = i;
                    active_element = ENEMY;
                } 
                
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    ImGui::Image(tex_enemies[i], ImVec2(64,64));
                    ImGui::EndTooltip();
                }
            }
        }
        ImGui::ListBoxFooter();
        
        
        //items list
        ImGui::PushStyleColor(ImGuiCol_Text, col_title_text);
        ImGui::Text("Items");
        ImGui::PopStyleColor();
        
        if (ImGui::ListBoxHeader("##itemslist", ImVec2(UI.LIST_WIDTH, UI.LIST_HEIGHT)))
        {   
            for (int i = 0; i < items_list.size(); ++i)
            {
                if(ImGui::Selectable(items_list[i].c_str(), active_item == i))
                {
                    active_item = i;
                    active_element = ITEM;
                }
                
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    ImGui::Image(tex_items[i], ImVec2(64,64));
                    ImGui::EndTooltip();
                }
            }
        }
        ImGui::ListBoxFooter();
        
        //backgrounds list
        ImGui::PushStyleColor(ImGuiCol_Text, col_title_text);
        ImGui::Text("Backgrounds");
        ImGui::PopStyleColor();
        
        if (ImGui::ListBoxHeader("##backgroundslist", ImVec2(UI.LIST_WIDTH, UI.LIST_HEIGHT)))
        {   
            for (int i = 0; i < backgrounds_list.size(); ++i)
            {
                if(ImGui::Selectable(std::to_string(backgrounds_list[i]).c_str(), active_background == i))
                {
                    active_background = i;
                    std::string str_num = std::to_string(i+1);
                    if (i < 9)
                    {
                        str_num = "0" + str_num;
                    }
                    std::string fname = "res/backgrounds/" + str_num + ".png";
                    tex_background.loadFromFile(fname, sf::IntRect(0, 0, 960, 768));
                }
                
                if (ImGui::IsItemHovered())
                {
                    std::string str_num = std::to_string(i+1);
                    if (i < 9)
                    {
                        str_num = "0" + str_num;
                    }
                    std::string fname = "res/backgrounds/" + str_num + ".png";
                    tex_background_thumb.loadFromFile(fname, sf::IntRect(0, 0, 960, 768));
                    
                    ImGui::BeginTooltip();
                    ImGui::Image(tex_background_thumb, ImVec2(64,64));
                    ImGui::EndTooltip();
                }
            }
        }
        ImGui::ListBoxFooter();
        
        ImGui::Spacing();
        
        // draw debug info
        ImGui::Text("mouse_x:");ImGui::SameLine();ImGui::Text(std::to_string(ImGui::GetMousePos().x).c_str());
        ImGui::Text("mouse_y:");ImGui::SameLine();ImGui::Text(std::to_string(ImGui::GetMousePos().y).c_str());
        
        ImGui::End();
        
        // MAIN
        ImGui::SetNextWindowSize(ImVec2(app_window_width - UI.MAIN_X - UI.MARGIN, app_window_height - (2 * UI.MARGIN)));
        ImGui::SetNextWindowPos(ImVec2(UI.MAIN_X, UI.MAIN_Y));
        ImGui::SetNextWindowContentSize(ImVec2(960 + UI.MARGIN + 4, 768 + UI.MARGIN));
        
        float bg_alpha = 0.0f; // this allows the grid to be visible over the background
        ImGui::SetNextWindowBgAlpha(bg_alpha);
        
        ImGui::Begin("main", false, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        
        draw_list = ImGui::GetWindowDrawList();
        
        // draw wireframe grid
        if (layer_grid.VISIBLE)
        {
            DrawGrid();
        }
        
        // store elements on mouse click
        if (ImGui::IsWindowHovered())
        {
            grid_hovered = true;
            current_row = (ImGui::GetMousePos().y - UI.GRID_START_Y) / 64;
            current_col = (ImGui::GetMousePos().x - UI.GRID_START_X) / 64;
            
            if (current_row > 11) current_row = 11;
            if (current_col > 14) current_col = 14;
            
            if (ImGui::IsMouseDown(0) && mode == MODE_PAINT)
            {
                grid[current_row][current_col].TYPE = active_element;
                sf::Texture &t = GetItemTexture(active_element);
                grid[current_row][current_col].SPRITE.setTexture(t);
                
                if (active_element == ENEMY)
                {
                    grid[current_row][current_col].SUBTYPE = active_enemy;
                }
                else if (active_element == ITEM)
                {
                    grid[current_row][current_col].SUBTYPE = active_item;
                }
            }
            
            if (ImGui::IsMouseDoubleClicked(0) && mode == MODE_EDIT)
            {
                if (grid[current_row][current_col].TYPE != BLOCK_VOID)
                {
                    ImGui::OpenPopup("Element Options");
                }
                
            }
        }
        else
        {
            grid_hovered = false;
        }
        
        OpenElementOptions(current_row, current_col);
        
        window.clear();
        
        // draw background
        if (layer_background.VISIBLE)
        {
            sf::Sprite back;
            back.setTexture(tex_background);
            back.setPosition(UI.GRID_START_X, UI.GRID_START_Y);
            window.draw(back);
        }
        
        // read grid vector and draw elements
        for (int i = 0; i < 12; ++i)
        {
            for (int j = 0; j < 15; ++j)
            {
                if (LayerIsVisible(grid[i][j].TYPE))
                {
                    window.draw(grid[i][j].SPRITE);
                }
            }
        }
        
        // set current item at mouse
        if (grid_hovered && mode == MODE_PAINT)
        {
            sf::Sprite s;
            s.setTexture(GetItemTexture(active_element));
            s.setPosition(sf::Vector2f(UI.GRID_START_X + (current_col*64), UI.GRID_START_Y + (current_row*64)));
            window.draw(s);
        }
        
        ImGui::End();
        
        ImGui::SFML::Render(window);
        
        window.display();
    }
    
    // shut down
    ImGui::SFML::Shutdown();
    
}
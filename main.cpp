#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <string>
#include <iostream>
#include <array>
#include <Windows.h>
#include <fstream>

#include "portable-file-dialogs.h"
#include "globals.cpp"
#include "func.cpp"

#pragma comment (lib, "Comdlg32")
#pragma comment (lib, "OLE32")
#pragma comment (lib, "shell32")

int main()
{
	sf::RenderWindow window(sf::VideoMode(1250, 800), "Open Solomon's Key Editor", sf::Style::Close);
	window.setPosition(ImVec2(0,0));
    window.setFramerateLimit(60);
	ImGui::SFML::Init(window);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
    sf::Clock deltaClock;
	
    //setup
    LoadTextures();
    InitLevel();
    active_element.TEXTURE = &tex_blocks[1];
    hidden_sprite.setTexture(tex_blocks[3]);
    
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
            else if(event.type == sf::Event::LostFocus)
            {
                window.setFramerateLimit(5);
            }
            else if(event.type == sf::Event::GainedFocus)
            {
                window.setFramerateLimit(60);
            }
		}
        
		ImGui::SFML::Update(window, deltaClock.restart());
        
        // TOOLBOX //////////////////////////////////////////////////////////
        int app_window_height = io.DisplaySize.y;
        int app_window_width = io.DisplaySize.x;
        
        ImGui::SetNextWindowSize(ImVec2(UI.TOOLBOX_WIDTH, app_window_height - (2 * UI.MARGIN)));
        ImGui::SetNextWindowPos(ImVec2(UI.TOOLBOX_X + UI.MARGIN, UI.TOOLBOX_Y + UI.MARGIN));
        ImGui::Begin("toolbox", false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
		
        // file operations
        if (ImGui::SmallButton("Open"))
        {
            // File open
            auto f = pfd::open_file("Open file", DEFAULT_PATH,
                                    { "Text Files (.txt .text)", "*.txt *.text",
                                    "All Files", "*" },
                                    false);
            
            //for (auto const &name : f.result())
            //std::cout << " " + name;
            std::cout << f.result()[0];
            std::cout << "\n";
            
            //read file here
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Save"))
        {
            // File save
            auto f = pfd::save_file("Save file", DEFAULT_PATH,
                                    { "Text Files (.txt .text)", "*.txt *.text",
                                    "All Files", "*" },
                                    true);
            
            std::cout << f.result();
            std::cout << "\n";
            
            SaveLevel(f.result());
        }
        ImGui::SameLine();
        if (ImGui::SmallButton("Help"))
        {
            ImGui::OpenPopup("help");
        }
        
        bool p_help_opened = true;
        if (ImGui::BeginPopupModal("help", &p_help_opened, ImGuiWindowFlags_NoResize))
        {
            ImGui::Text("Open Solomon's Key Editor. By Immortalx. (v 1.0 05/2020)\n\n");
            ImGui::Text("How to use:");
            ImGui::Text("Select an element from the toolbox and paint it on the grid.");
            ImGui::Text("The empty block erases any previously painted elements.\n\n");
            ImGui::Text("Unique elements are those that can only be placed once in the level.");
            ImGui::Text("You have to place one of each to generate a valid level.\n\n");
            ImGui::Text("Right-click an existing element on the grid to access its properties.");
            ImGui::Text("Most enemies, for example, have an initial direction and speed.\n\n");
            ImGui::Text("There are 2 types of items in Solomon's key: Visible and hidden.");
            ImGui::Text("Those that are visible can be placed directly on the grid.");
            ImGui::Text("Hidden items can only be placed under the brown-ish destructible blocks,");
            ImGui::Text("or on any empty cell on the grid.");
            ImGui::Text("To place such an item, right-click an existing destructible block,");
            ImGui::Text("or an empty cell to access its properties.");
            ImGui::Text("Then check 'Contains hidden item' and select an item from the list.\n\n");
            ImGui::Text("Solomon's Key is a copyright of Tecmo.");
            ImGui::Text("(NOTE: This is a fun-made editor, meant to be used alongside an");
            ImGui::Text("also fun-made re-creation of the game.)");
            if (ImGui::Button("OK", ImVec2(80,0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        
        ImGui::Text("Show/Hide grid");
        
        ImGui::Checkbox("Grid", &show_grid);
        
        // render active tile
        ImVec2 cur_pos = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(UI.TOOLBOX_X + 180, UI.TOOLBOX_Y + 37));
        ImGui::Text("Selected");
        ImGui::SetCursorPosX(UI.TOOLBOX_X + 174);
        ImGui::Image(*active_element.TEXTURE);
        
        ImGui::SetCursorPos(cur_pos);
        ImGui::SetCursorPosY(cur_pos.y + 40.0f);
        ImGui::Spacing();
        
        // blocks
        ImGui::Text("Blocks");
        
        if (ImGui::ImageButton(tex_blocks[0], ImVec2(64,64)))
        {
            active_element.TEXTURE = &tex_blocks[0];
            active_element.TYPE = BLOCK;
            active_element.INDEX = 0;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton(tex_blocks[1], ImVec2(64,64)))
        {
            active_element.TEXTURE = &tex_blocks[1];
            active_element.TYPE = BLOCK;
            active_element.INDEX = 1;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton(tex_blocks[2], ImVec2(64,64)))
        {
            active_element.TEXTURE = &tex_blocks[2];
            active_element.TYPE = BLOCK;
            active_element.INDEX = 2;
        }
        
        ImGui::Spacing();
        
        
        //unique elements
        ImGui::Text("Unique elements");
        
        if (ImGui::ImageButton(tex_unique[0], ImVec2(64,64)))
        {
            active_element.TEXTURE = &tex_unique[0];
            active_element.TYPE = UNIQUE;
            active_element.INDEX = 0;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton(tex_unique[1], ImVec2(64,64)))
        {
            active_element.TEXTURE = &tex_unique[1];
            active_element.TYPE = UNIQUE;
            active_element.INDEX = 1;
        }
        ImGui::SameLine();
        if (ImGui::ImageButton(tex_unique[2], ImVec2(64,64)))
        {
            active_element.TEXTURE = &tex_unique[2];
            active_element.TYPE = UNIQUE;
            active_element.INDEX = 2;
        }
        
        ImGui::Spacing();
        
        //enemies list
        ImGui::Text("Enemies");
        
        if (ImGui::ListBoxHeader("##enemieslist", ImVec2(UI.LIST_WIDTH, UI.LIST_HEIGHT)))
        {   
            for (int i = 0; i < NUM_ENEMIES; ++i)
            {
                if(ImGui::Selectable(enemies_list[i]/*, active_enemy == i*/))
                {
                    SetActiveTile(ENEMY, i);
                    active_element.TYPE = ENEMY;
                    active_element.INDEX = i;
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
        ImGui::Text("Items");
        
        if (ImGui::ListBoxHeader("##itemslist", ImVec2(UI.LIST_WIDTH, UI.LIST_HEIGHT)))
        {   
            for (int i = 0; i < NUM_ITEMS; ++i)
            {
                if(ImGui::Selectable(items_list[i]/*, active_item == i*/))
                {
                    SetActiveTile(ITEM, i);
                    active_element.TYPE = ITEM;
                    active_element.INDEX = i;
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
        ImGui::Text("Backgrounds");
        
        if (ImGui::ListBoxHeader("##backgroundslist", ImVec2(UI.LIST_WIDTH, UI.LIST_HEIGHT)))
        {   
            for (int i = 0; i < NUM_BACKGROUNDS; ++i)
            {
                if(ImGui::Selectable(std::to_string(i).c_str()))
                {
                    background_index = i;
                }
                
                if (ImGui::IsItemHovered())
                {
                    ImGui::BeginTooltip();
                    ImGui::Image(tex_backgrounds[i], ImVec2(64,64));
                    ImGui::EndTooltip();
                }
            }
        }
        ImGui::ListBoxFooter();
        
        ImGui::Spacing();
        
        // draw debug info
        //ImGui::Text("mouse_x:");ImGui::SameLine();ImGui::Text(std::to_string(ImGui::GetMousePos().x).c_str());
        //ImGui::Text("mouse_y:");ImGui::SameLine();ImGui::Text(std::to_string(ImGui::GetMousePos().y).c_str());
        
        ImGui::End();
        
        
        // MAIN WINDOW ////////////////////////////////////////////////////////
        ImGui::SetNextWindowSize(ImVec2(app_window_width - UI.MAIN_X - UI.MARGIN, app_window_height - (2 * UI.MARGIN)));
        ImGui::SetNextWindowPos(ImVec2(UI.MAIN_X, UI.MAIN_Y));
        ImGui::SetNextWindowContentSize(ImVec2(960 + UI.MARGIN + 4, 768 + UI.MARGIN));
        
        // this allows the grid to be visible over the background
        float bg_alpha = 0.0f;
        ImGui::SetNextWindowBgAlpha(bg_alpha);
        
        ImGui::Begin("main", false, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        
        draw_list = ImGui::GetWindowDrawList();
        
        // draw grid
        if (show_grid)
        {
            DrawGrid();
        }
        
        // store elements
        if (ImGui::IsWindowHovered())
        {
            int idx = GetCellIndex();
            
            //show hidden item on hover
            if(level[idx].CONTAINS_HIDDEN)
            {
                ImGui::BeginTooltip();
                ImGui::Image(tex_items[level[idx].HIDDEN_ITEM_INDEX], ImVec2(64,64));
                ImGui::EndTooltip();
            }
            
            //Set property popup to open
            if(ImGui::IsMouseClicked(1))
            {
                property_mode = true;
                element_index = idx;
                ImGui::OpenPopup("Element Options");
            }
            
            if (ImGui::IsMouseDown(0))
            {
                if(!property_mode)
                {
                    CheckForUniquePresence(idx);
                    PlaceSelectedElement(idx);
                }
            }
        }
        
        //properties popup
        OpenPropertiesWindow();
        
        // start draw
        window.clear();
        
        //draw background
        background_sprite.setTexture(tex_backgrounds[background_index]);
        background_sprite.setPosition(UI.GRID_START_X, UI.GRID_START_Y);
        window.draw(background_sprite);
        
        //draw level
        DrawLevel(window);
        //ImGui::ShowDemoWindow();
        ImGui::End();
        ImGui::SFML::Render(window);
        window.display();
    }
    
    // shut down
    ImGui::SFML::Shutdown();
    
}
void LoadTextures()
{
	int x_offset = 0;
	int y_offset = 0;
    sf::Texture t;
    
	// blocks
    for (int i = 0; i < NUM_BLOCKS; ++i)
	{
	    t.loadFromFile("res/blocks.png", sf::IntRect(x_offset, 0, 64, 64));
	    tex_blocks[i] = t;
	    x_offset += 64;
	}
    
    // unique
    x_offset = 0;
    for (int i = 0; i < NUM_UNIQUE; ++i)
	{
	    t.loadFromFile("res/unique.png", sf::IntRect(x_offset, 0, 64, 64));
	    tex_unique[i] = t;
	    x_offset += 64;
	}
    
    // enemies
    x_offset = 0;
    for (int i = 0; i < NUM_ENEMIES; ++i)
    {
        if (i == 7)
        {
            x_offset = 0;
            y_offset = 64;
        }
        
        t.loadFromFile("res/enemies.png", sf::IntRect(x_offset, y_offset, 64, 64));
	    tex_enemies[i] = t;
        x_offset += 64;
    }
    
    // items
    x_offset = 0;
    y_offset = 0;
    for (int i = 0; i < NUM_ITEMS; ++i)
    {
        if (i == 7)
        {
            x_offset = 0;
            y_offset = 64;
        }
        
        t.loadFromFile("res/items.png", sf::IntRect(x_offset, y_offset, 64, 64));
	    tex_items[i] = t;
        x_offset += 64;
    }
    
    //backgrounds
    for (int i = 0; i < NUM_BACKGROUNDS; ++i)
    {
        backgrounds_list[i] = i;
        
        t.loadFromFile("res/backgrounds/" + std::to_string(i) + ".png");
	    tex_backgrounds[i] = t;
    }
}

void SetActiveTile(TILE_TYPE t, int index)
{
    switch (t)
    {
        case ENEMY:
        active_element.TEXTURE = &tex_enemies[index];
        break;
        
        case ITEM:
        active_element.TEXTURE = &tex_items[index];
        break;
        
        default:
        active_element.TEXTURE = &tex_blocks[1];
    }
}

void InitLevel()
{
    float xx = UI.GRID_START_X;
    float yy = UI.GRID_START_Y;
    
    int count = 0;
    
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            level[count].SPRITE.setTexture(tex_blocks[0]);
            level[count].SPRITE.setPosition(xx, yy);
            
            xx += 64.0f;
            count++;
        }
        
        xx = UI.GRID_START_X;
        yy += 64.0f;
    }
}

void DrawLevel(sf::RenderWindow &w)
{
    for (int i = 0; i < 180; ++i)
    {
        w.draw(level[i].SPRITE);
        
        if(level[i].CONTAINS_HIDDEN)
        {
            //std::cout << i << std::endl;
            sf::Vector2f pos;
            pos = level[i].SPRITE.getPosition();
            hidden_sprite.setPosition(pos);
            w.draw(hidden_sprite);
        }
    }
}

void DrawGrid()
{
    int x_offset = UI.MAIN_X + UI.MARGIN + 4 - ImGui::GetScrollX();
    int y_offset = UI.MAIN_Y + UI.MARGIN + 4 - ImGui::GetScrollY();
    int y_start = y_offset;
    
    for (int i = 0; i <= 12; ++i)
    {
        for (int j = 0; j <= 15; ++j)
        {
            draw_list->AddLine(ImVec2(x_offset, y_start), ImVec2(x_offset, y_start + UI.GRID_HEIGHT), grid_color);
            x_offset += 64;
        }
        
        x_offset = UI.MAIN_X + UI.MARGIN + 4 - ImGui::GetScrollX();
        draw_list->AddLine(ImVec2(x_offset, y_offset), ImVec2(x_offset + UI.GRID_WIDTH, y_offset), grid_color);
        y_offset += 64;
    }
}

void SaveLevel(std::string filename)
{
    std::ofstream file;
    file.open(filename);
    
    if (!file)
    {
        std::cout << "Error opening file\n";
    }
    file << "#Auto-generated from osked\n";
    file << "\n";
    file << "background=";
    file << "\n";
    file << "\n";
    
    for (int i = 0; i < 180; ++i)
    {
        if(i % 15 == 0 && i > 0)
        {
            file << "\n";
        }
        
        if(level[i].TYPE == BLOCK)
        {
            file << level[i].INDEX;
            
            if(level[i].CONTAINS_HIDDEN)
            {
                file << ",";
                file << level[i].HIDDEN_ITEM_INDEX;
            }
        }
        else if(level[i].TYPE == UNIQUE)
        {
            if(level[i].INDEX == 0)
            {
                file << 4;//dana
            }
            if(level[i].INDEX == 1)
            {
                file << 7;//door
            }
            if(level[i].INDEX == 2)
            {
                file << 8;//key
            }
        }
        else if(level[i].TYPE == ENEMY)
        {
            file << 6;//ENEMY
            file << ",";
            file << level[i].INDEX;
            file << ",";
            file << level[i].SPEED;
            file << ",";
            file << level[i].DIR;
        }
        else if(level[i].TYPE == ITEM)
        {
            file << 10;//ITEM
            file << ",";
            file << level[i].INDEX;
        }
        
        file << " ";
        
        
    }
    
    file.close();
}

int GetCellIndex()
{
    int current_row = (ImGui::GetMousePos().y - UI.GRID_START_Y) / 64;
    int current_col = (ImGui::GetMousePos().x - UI.GRID_START_X) / 64;
    if (current_row > 11) current_row = 11;
    if (current_col > 14) current_col = 14;
    int idx = (current_row  * 15) + current_col;
    
    return idx;
}

void OpenPropertiesWindow()
{
    if(ImGui::BeginPopupModal("Element Options", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        int el_type = level[element_index].TYPE;
        
        if(el_type == ENEMY)
        {
            ImGui::Text("Initial Speed");
            int speed = level[element_index].SPEED;
            if(ImGui::SliderInt("##Speed", &speed, MIN_SPEED, MAX_SPEED))
            {
                level[element_index].SPEED = speed;
            }
            
            ImGui::Spacing();ImGui::Spacing();
            
            ImGui::Text("Initial direction");
            int dir = level[element_index].DIR;
            
            if(ImGui::RadioButton("Left", &dir, 0))
            {
                level[element_index].DIR = dir;
            }
            if(ImGui::RadioButton("Right", &dir, 1))
            {
                level[element_index].DIR = dir;
            }
            if(ImGui::RadioButton("Up", &dir, 2))
            {
                level[element_index].DIR = dir;
            }
            if(ImGui::RadioButton("Down", &dir, 3))
            {
                level[element_index].DIR = dir;
            }
        }
        
        else if(el_type == BLOCK && level[element_index].INDEX != 2)
        {
            bool hidden_item = level[element_index].CONTAINS_HIDDEN;
            if(ImGui::Checkbox("Contains hidden item", &hidden_item))
            {
                hidden_item = !hidden_item;
                level[element_index].CONTAINS_HIDDEN = !level[element_index].CONTAINS_HIDDEN;
            }
            
            if(hidden_item)
            {
                //items list
                ImGui::Text("Hidden Item: ");
                ImGui::SameLine();
                ImGui::Text(items_list[level[element_index].HIDDEN_ITEM_INDEX]);
                
                if (ImGui::ListBoxHeader("##hiddenitem", ImVec2(UI.LIST_WIDTH, UI.LIST_HEIGHT)))
                {   
                    for (int i = 0; i < NUM_ITEMS; ++i)
                    {
                        if(ImGui::Selectable(items_list[i]))
                        {
                            level[element_index].HIDDEN_ITEM_INDEX = i;
                        }
                        
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::Image(tex_items[i], ImVec2(64,64));
                            ImGui::EndTooltip();
                        }
                    }
                    ImGui::ListBoxFooter();
                }
            }
        }
        
        if (ImGui::Button("Close", ImVec2(80,0)))
        {
            property_mode = false;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
}

void CheckForUniquePresence(int idx)
{
    //prevent unique tiles getting set more than once
    if(active_element.INDEX == 0 && active_element.TYPE == UNIQUE)
    {
        if(last_dana_index != -1)
        {
            level[last_dana_index].SPRITE.setTexture(tex_blocks[0]);
        }
        last_dana_index = idx;
    }
    if(active_element.INDEX == 1 && active_element.TYPE == UNIQUE)
    {
        if(last_door_index != -1)
        {
            level[last_door_index].SPRITE.setTexture(tex_blocks[0]);
        }
        last_door_index = idx;
    }
    if(active_element.INDEX == 2 && active_element.TYPE == UNIQUE)
    {
        if(last_key_index != -1)
        {
            level[last_key_index].SPRITE.setTexture(tex_blocks[0]);
        }
        last_key_index = idx;
    }
}

void PlaceSelectedElement(int idx)
{
    level[idx].SPRITE.setTexture(*active_element.TEXTURE);
    level[idx].TYPE = active_element.TYPE;
    level[idx].INDEX = active_element.INDEX;
    //reset all other properties to defaults
    level[idx].SPEED = DEFAULT_SPEED;
    level[idx].DIR = DEFAULT_DIR;
    level[idx].CONTAINS_HIDDEN = false;
    level[idx].HIDDEN_ITEM_INDEX = 0;
}
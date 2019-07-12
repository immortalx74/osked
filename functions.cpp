//

void DrawGrid()
{
    int x_offset = UI.MAIN_X + UI.MARGIN + 4 - ImGui::GetScrollX();
    int y_offset = UI.MAIN_Y + UI.MARGIN + 4 - ImGui::GetScrollY();
    int y_start = y_offset;
    
    for (int i = 0; i <= 12; ++i)
    {
        for (int j = 0; j <= 15; ++j)
        {
            draw_list->AddLine(ImVec2(x_offset, y_start), ImVec2(x_offset, y_start + UI.GRID_HEIGHT), col_grid);
            x_offset += 64;
        }
        
        x_offset = UI.MAIN_X + UI.MARGIN + 4 - ImGui::GetScrollX();
        draw_list->AddLine(ImVec2(x_offset, y_offset), ImVec2(x_offset + UI.GRID_WIDTH, y_offset), col_grid);
        y_offset += 64;
    }
}

void LoadTextures()
{
	int x_offset = 0;
	int y_offset = 0;
    sf::Texture t;
    
	// blocks
    for (int i = 0; i < 3; ++i)
	{
	    t.loadFromFile("res/blocks.png", sf::IntRect(x_offset, 0, 64, 64));
	    tex_blocks.push_back(t);
	    x_offset += 64;
	}
    
    // unique
    x_offset = 0;
    for (int i = 0; i < 3; ++i)
	{
	    t.loadFromFile("res/unique.png", sf::IntRect(x_offset, 0, 64, 64));
	    tex_unique.push_back(t);
	    x_offset += 64;
	}
    
    // enemies
    x_offset = 0;
    for (int i = 0; i < 14; ++i)
    {
        if (i == 7)
        {
            x_offset = 0;
            y_offset = 64;
        }
        
        t.loadFromFile("res/enemies.png", sf::IntRect(x_offset, y_offset, 64, 64));
	    tex_enemies.push_back(t);
        
        x_offset += 64;
    }
    
    // items
    x_offset = 0;
    y_offset = 0;
    for (int i = 0; i < 14; ++i)
    {
        if (i == 7)
        {
            x_offset = 0;
            y_offset = 64;
        }
        
        t.loadFromFile("res/items.png", sf::IntRect(x_offset, y_offset, 64, 64));
	    tex_items.push_back(t);
        
        x_offset += 64;
    }
    
    //backgrounds
    for (int i = 0; i < 27; ++i)
    {
        backgrounds_list.push_back(i);
    }
}

sf::Texture& GetItemTexture(ELEMENT_TYPE el_type)
{
    switch (el_type)
    {
        case BLOCK_VOID:
        return tex_blocks[0];
        break;
        
        case BLOCK_REGULAR:
        return tex_blocks[1];
        break;
        
        case BLOCK_SOLID:
        return tex_blocks[2];
        break;
        
        case UNIQUE_PLAYER:
        return tex_unique[0];
        break;
        
        case UNIQUE_DOOR:
        return tex_unique[1];
        break;
        
        case UNIQUE_KEY:
        return tex_unique[2];
        break;
        
        case ENEMY:
        return tex_enemies[active_enemy];
        break;
        
        case ITEM:
        return tex_items[active_item];
        break;
        
        default:
        return tex_blocks[0];
    }
}

void InitGrid()
{
    
    int xx = UI.GRID_START_X;
    int yy = UI.GRID_START_Y;
    
    for (int i = 0; i < 12; ++i)
    {
        std::vector<GRID> row;
        
        for (int j = 0; j < 15; ++j)
        {
            GRID row_data;
            
            row_data.SPRITE.setTexture(GetItemTexture(BLOCK_VOID));
            row_data.SPRITE.setPosition(sf::Vector2f(xx, yy));
            row_data.TYPE = BLOCK_VOID;
            row_data.SUBTYPE = -1;
            row_data.ATTR1 = 0;
            row_data.ATTR2 = 0;
            
            row.push_back(row_data);
            
            xx += 64;
        }
        xx = UI.GRID_START_X;
        yy += 64;
        grid.push_back(row);
    }
}

bool LayerIsVisible(ELEMENT_TYPE el_type)
{
    switch (el_type)
    {
        case BLOCK_VOID:case BLOCK_SOLID:case BLOCK_REGULAR:
        if (!layer_blocks.VISIBLE)
        {
            return false;
        }
        return true;
        break;
        
        case UNIQUE_PLAYER:case UNIQUE_DOOR:case UNIQUE_KEY:
        if (!layer_unique.VISIBLE)
        {
            return false;
        }
        return true;
        break;
        
        case ENEMY:
        if (!layer_enemies.VISIBLE)
        {
            return false;
        }
        return true;
        break;
        
        case ITEM:
        if (!layer_items.VISIBLE)
        {
            return false;
        }
        return true;
        break;
        
        default:
        return true;
    }
}

void OpenElementOptions(int row, int col)
{
    bool p_opened = true;
    ImGui::SetNextWindowSize(ImVec2(300, 200));
    if (ImGui::BeginPopupModal("Element Options", &p_opened, ImGuiWindowFlags_NoResize))
    {
        std::string location = "Element at row:" + std::to_string(current_row)
            + ", col:" + std::to_string(current_col);
        
        
        
        ImGui::Text(location.c_str());
        
        if (ImGui::Button("OK", ImVec2(80,0)))
        {
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Cancel", ImVec2(80,0)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}
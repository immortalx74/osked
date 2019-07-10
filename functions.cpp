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
	sf::Texture t;
    
	for (int i = 0; i < 3; ++i)
	{
	    if (!t.loadFromFile("res/blocks/blocks.png", sf::IntRect(x_offset, 0, 64, 64)))
	    {
	        std::cout << "error";
	    }
		
	    tex_blocks.push_back(t);
	    x_offset += 64;
	}
    
    //x_offset = 0;
    
}
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
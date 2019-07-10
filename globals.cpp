//
struct LAYER
{
    std::string NAME;
    bool VISIBLE;
};

struct UI_SIZING
{
	float MARGIN = 4;
    
	float TOOLBOX_X = 0;
	float TOOLBOX_Y = 0;
	float TOOLBOX_WIDTH = 260;
	float TOOLBOX_HEIGHT = 0;
    
    float MAIN_X = TOOLBOX_WIDTH + (2 * MARGIN);
    float MAIN_Y = MARGIN;
    float MAIN_WIDTH = 0;
    float MAIN_HEIGHT = 0;
    
    float GRID_START_X = MAIN_X + (2 * MARGIN);
    float GRID_START_Y = MAIN_Y + (2 * MARGIN);
    float GRID_WIDTH = 960;
    float GRID_HEIGHT = 768;
};

//struct GRID
//{
//
//};

enum ELEMENT_TYPE
{
    BLOCK,
    ENEMY,
    ITEM,
    UNIQUE
};

struct ACTIVE_ELEMENT
{
    ELEMENT_TYPE TYPE;
    std::vector<int> FLAGS = {0};
};

UI_SIZING UI;
LAYER layer_grid = {"Grid", true};
LAYER layer_blocks = {"Blocks", true};
LAYER layer_enemies = {"Enemies", true};
LAYER layer_items = {"Items", true};
LAYER layer_background = {"Background", true};


int col_title_text = IM_COL32(255,130,0,255);
int col_normal_text = IM_COL32(255,255,255,255);
int col_grid = IM_COL32(255,130,0,255);

//std::vector<TRACK> tracks_list;
//std::vector<std::vector<NOTE_DATA>> module;

ImDrawList* draw_list;
ACTIVE_ELEMENT active_element;

std::vector<sf::Texture> tex_blocks;

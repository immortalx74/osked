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
    
    float LIST_WIDTH = 230;
    float LIST_HEIGHT = 100;
    
    float GRID_START_X = MAIN_X + (2 * MARGIN);
    float GRID_START_Y = MAIN_Y + (2 * MARGIN);
    float GRID_WIDTH = 960;
    float GRID_HEIGHT = 768;
};

enum ELEMENT_TYPE
{
    BLOCK_VOID,
    BLOCK_REGULAR,
    BLOCK_SOLID,
    UNIQUE_PLAYER,
    UNIQUE_DOOR,
    UNIQUE_KEY,
    ENEMY,
    ITEM,
};

struct GRID
{
    sf::Sprite SPRITE;
    ELEMENT_TYPE TYPE;
    int SUBTYPE;
    int ATTR1;
    int ATTR2;
};

UI_SIZING UI;
LAYER layer_grid = {"Grid", true};
LAYER layer_blocks = {"Blocks", true};
LAYER layer_enemies = {"Enemies", true};
LAYER layer_items = {"Items", true};
LAYER layer_unique = {"Unique", true};
LAYER layer_background = {"Background", true};


int col_title_text = IM_COL32(255,130,0,255);
int col_normal_text = IM_COL32(255,255,255,255);
int col_grid = IM_COL32(255,255,255,255);

ImDrawList* draw_list;
ELEMENT_TYPE active_element = BLOCK_VOID;

int active_enemy = 0;
int active_item = 0;
int active_background = 0;

int current_row = 0;
int current_col = 0;
bool grid_hovered = false;

std::vector<sf::Texture> tex_blocks;
std::vector<sf::Texture> tex_unique;
std::vector<sf::Texture> tex_enemies;
std::vector<sf::Texture> tex_items;

sf::Texture tex_background;
sf::Texture tex_background_thumb;

std::vector<std::vector<GRID>> grid;

std::vector<std::string> enemies_list ={
    "Chimera",
    "Demonhead",
    "Dragon",
    "Gargoyle",
    "Ghost",
    "Goblin",
    "Nuel",
    "Salamander",
    "Wyvern",
    "Panel Monster",
    "Earth Mage",
    "Spark Ball",
    "Flame",
    "Spawn Gate"
};

std::vector<std::string> items_list = {
    "Bag 10K",
    "Bag 20K",
    "Bag 100",
    "Bag 200",
    "Bag 500",
    "Bag 1000",
    "Bag 2000",
    "Bag 5000",
    "Bell",
    "Coin 20K",
    "Coin 1000",
    "Coin 2000",
    "Coin 10000",
    "Destruction Potion"
};

std::vector<int> backgrounds_list;
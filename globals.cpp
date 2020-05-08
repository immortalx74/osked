#define DEFAULT_PATH "C:\\"

#define NUM_BLOCKS 4
#define NUM_UNIQUE 3
#define NUM_ENEMIES 14
#define NUM_ITEMS 14
#define NUM_BACKGROUNDS 27

#define DEFAULT_SPEED 3
#define MIN_SPEED 1
#define MAX_SPEED 10
#define DEFAULT_DIR 1

struct METRICS
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
    float LIST_HEIGHT = 120;
    
    float GRID_START_X = MAIN_X + (2 * MARGIN);
    float GRID_START_Y = MAIN_Y + (2 * MARGIN);
    float GRID_WIDTH = 960;
    float GRID_HEIGHT = 768;
}UI;

sf::Texture tex_blocks[NUM_BLOCKS];
sf::Texture tex_unique[NUM_UNIQUE];
sf::Texture tex_enemies[NUM_ENEMIES];
sf::Texture tex_items[NUM_ITEMS];
sf::Texture tex_backgrounds[NUM_BACKGROUNDS];

const char *enemies_list[NUM_ENEMIES] = {
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
    "Kameera Mirror"
};

const char *items_list[NUM_ITEMS] = {
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

int backgrounds_list[NUM_BACKGROUNDS];

enum TILE_TYPE
{
    BLOCK,
    UNIQUE,
    ENEMY,
    ITEM
};

struct ACTIVE_ELEMENT
{
    sf::Texture *TEXTURE = 0;
    int INDEX = 1;
    TILE_TYPE TYPE = BLOCK;
}active_element;

struct CELL
{
    sf::Sprite SPRITE;
    TILE_TYPE TYPE = BLOCK;
    int INDEX = 0;
    
    bool CONTAINS_HIDDEN = false;
    int HIDDEN_ITEM_INDEX = 0;
    
    int SPEED = DEFAULT_SPEED;
    int DIR = DEFAULT_DIR;
};

CELL level[180];

int last_dana_index = -1;
int last_door_index = -1;
int last_key_index = -1;
int background_index = 0;

sf::Sprite background_sprite;
sf::Sprite hidden_sprite;
bool show_grid = true;
ImDrawList* draw_list;
int grid_color = IM_COL32(255,255,255,255);

int current_row = 0;
int current_col = 0;

bool property_mode = false;
int element_index = 0;
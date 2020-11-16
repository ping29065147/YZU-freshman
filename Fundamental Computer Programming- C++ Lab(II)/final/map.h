#ifndef MAP
#define MAP
#include <vector>
#include <string>
#include "player.h"
using namespace std;

struct map_type 
{
	string map_data;
	vector<int> map_color;
};

struct origins
{
	char _ch;
	int _color;
};

class map
{

public:
	map();

	//set the data of player in account to map
	void set_player(player& Mp);

	//print the yzumap
	void print_map();

	//player moves
	int move();

	void show_cursor();

private:
	vector<map_type> yzumap;

	//the player position (x, y)
	int x, y;
	
	player* myplayer;

	//store the origin position
	origins origin;

	//load yzumap from yzumap.txt
	void load();

	//determine what will do next
	int determine(char ch);

	//check the next step
	int encounter();
};


#endif //MAP
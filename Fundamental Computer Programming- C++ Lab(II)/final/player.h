#ifndef PLAYER
#define PLAYER
#include "pokemon database.h"
#include "ability.h"

//npc's pokemons and location
struct NPC_data
{
	vector<int> poks;
	int _x;
	int _y;
};

//the status of a battle
struct battle_data
{
	int hp;
	int atk;
	int def;
	int spd;
	int special;
};

class player
{
public:
	player();

	int getx();
	int gety();
	int get_topography();
	size_t get_mypokemons_size(); // get mypokemon's amount
	vector<int> get_mypokemons(); //return mypokemons
	int get_npc_n(); // get current npc
	bool* get_victory();
	int get_victory_times();

	void setxy(int X, int Y);
	void set_topography(int topo);
	void set_my_pok(int* my_pok);
	void set_victory(bool* vic);

	//catch pokemon
	void catch_pokemon();

	//open backpack
	void print_backpack();

	//check attribute
	void print_atb();

	//set the npc's pokemons and location
	void set_NPC(int p1, int p2, int p3, int x, int y);

	void battle();

	//initialization the battle data
	void set_battle_data();

	battle_data get_player_battle_data();
	battle_data get_npc_battle_data();

	//check if pokemon is alive of not
	bool check_hp(bool* alive, int& located, int& npc_count, battle_data c1, battle_data c2);

	//clean a line
	void clean_line(int line);

	//according to the attribute, set tthe damage rate
	void set_damage_rate(int p, int n);

private:
	int x, y;
	vector<int> mypokemons;
	int topography;
	bool victory[12];

	//all pokemon data
	pokemon_database Pokemon_database;

	base_pokemon* current_pok;
	base_pokemon* npc_pok;
	NPC_data current_npc;

	//all npc
	vector< NPC_data > NPC;

	//player's(0-2) and npc's(3-5) battle data
	vector<battle_data> lists;

	int old_hp;
	double damage_rate_player;
	double damage_rate_npc;
};


#endif //PLAYER
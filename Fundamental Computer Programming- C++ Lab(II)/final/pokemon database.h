#ifndef POKEMON_DATABASE
#define POKEMON_DATABASE
#include <vector>
#include <string>

using namespace std;

struct pokemon
{
	vector<string> picture;
	int no;
	string name;
	string type;
	int hp;
	int atk;
	int def;
	int speed;
	int ability;
};

class pokemon_database
{

public:
	pokemon_database();
	
	void print_catch(int no);
	void print_battle(int no, int no2, vector<int> player, vector<int> npc, bool* p_num, int n_num);
	void print_attribute();

	template <typename T>
	int get_no(T no);
	template <typename T>
	string get_name(T no);
	template <typename T>
	string get_type(T no);
	pokemon get_pokemon(int no);
	double get_attribute(int atk, int def);

private:
	vector<pokemon> pokemons;
	vector< vector<double> > attribute;

	void load_pokemon();
	void load_picture();
	void load_attribute();
};




#endif //POKEMON_DATABASE
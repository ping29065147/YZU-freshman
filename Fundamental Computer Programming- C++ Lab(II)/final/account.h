#ifndef INPUT
#define INPUT
#include <vector>
#include <string>
#include "player.h"
using namespace std;

struct mydata 
{
	char name[21];
	char account_number[21];
	char passward[21];

	//location of the player
	int x;
	int y;
	int topography;

	int mypokemons[3];
	bool victory[12];
};

class account
{

public:
	account();
	~account();

	//to set the reference of myplayer in account to map
	player& get_player();

	int print_menu();

	//enter name, account number, passward to create an account
	void create_account();

	//search from account_data if the account number and passward are exist
	bool login();

	//catch pokemon
	void catch_pok();

	//battle with npc
	void battled();

	//leave the game
	bool _exit();

	//return using account
	mydata* get_account();

	//set the data in account to player
	void load_player(mydata* my_acc);

	//open backpack
	void backpack();

	//check attribute
	void attribute();

private:
	vector<mydata> account_data;

	//pointer to using account
	mydata* now;
	
	//load all accounts from account data.dat
	void load_data();

	//store all accounts to account data.dat
	void store_data();

	//check the input of name, account number, passward
	void input_range(size_t begin, size_t end, char* temp, bool check = false);

	//return true if the account is existence
	bool exist(char* account_number);

	player myplayer;
};

#endif //INPUT
#include <iostream>
#include <time.h>
#include "monster.h"

int main(int argc, const char *argv[])
{
    srand(time(NULL));

	Player player1("player1");
	Player player2("player2");

	int count_battle = 1;
	while (1) {
		if (player1.getCurrentMonster() == nullptr) {
			std::cout << "\n\n" << player2.getName() << " win!!!\n";  //player2 win
			break;
		}
		else if (player2.getCurrentMonster() == nullptr) {
			std::cout << "\n\n" << player1.getName() << " win!!!\n";  //player1 win
			break;
		}

		std::cout << "Battle " << count_battle++ << std::endl;

		int first_attack = rand() % 2; //decide who attack first
		int count_round = 1;
		while (1) {
			std::cout << "Round " << count_round++ << std::endl << std::endl;
			if (first_attack) {
				player1.getCurrentMonster()->attack( *player2.getCurrentMonster() );
				cout << player2.getName() << " ";
				player2.getCurrentMonster()->showStats(); //show data
				if (player2.getCurrentMonster()->getHP() <= 0) { //if the monster is dead
					cout << player1.getName() << " ";
					player1.getCurrentMonster()->showStats();
					std::cout << "===============================" << std::endl;
					std::cout << ">>> player2 died! <<<" << std::endl << std::endl;
					player2.dead();
					break;
				}
				player2.getCurrentMonster()->attack( *player1.getCurrentMonster() );
				cout << player1.getName() << " ";
				player1.getCurrentMonster()->showStats();
				if (player1.getCurrentMonster()->getHP() <= 0) {
					std::cout << "===============================" << std::endl;
					std::cout << ">>> player1 died! <<<" << std::endl << std::endl;
					player1.dead();
					break;
				}
				std::cout << "===============================" << std::endl;
			}
			else {
				player2.getCurrentMonster()->attack( *player1.getCurrentMonster() );
				cout << player1.getName() << " ";
				player1.getCurrentMonster()->showStats();
				if (player1.getCurrentMonster()->getHP() <= 0) {
					cout << player2.getName() << " ";
					player2.getCurrentMonster()->showStats();
					std::cout << "===============================" << std::endl;
					std::cout << ">>> player1 died! <<<" << std::endl << std::endl;
					player1.dead();
					break;
				}
				player1.getCurrentMonster()->attack( *player2.getCurrentMonster() );
				cout << player2.getName() << " ";
				player2.getCurrentMonster()->showStats();
				if (player2.getCurrentMonster()->getHP() <= 0) {
					std::cout << "===============================" << std::endl;
					std::cout << ">>> player2 died! <<<" << std::endl << std::endl;
					player2.dead();
					break;
				}
				std::cout << "===============================" << std::endl;
			}
		}
		std::cout << player1.getName() << " alive monsters:\n";  //show alive monsters
		player1.showAliveMonsters();
		std::cout << "\n" << player2.getName() << " alive monsters:\n";
		player2.showAliveMonsters();
		std::cout << "\n\n";

		system("pause");
		system("cls");
	}

    return 0;
}

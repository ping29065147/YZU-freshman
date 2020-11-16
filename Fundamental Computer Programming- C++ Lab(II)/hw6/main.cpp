#include <iostream>
#include <time.h>
#include "monster.h"

int main(int argc, const char *argv[])
{
    srand(time(NULL));
    Dragon m1(0.6);
    Unicorn m2;

    int cnt = 1;
    int first_attack = rand() % 2; //decide who attack first
    while(true){
        std::cout << "Round " << cnt << std::endl;
        if (first_attack) 
           goto first_dragon;

    second_unicorn:
        m1.attack(m2);
        m2.showStats();
        if( m2.getHP() <= 0 ){
            std::cout << ">>> Unicorn died, Dragon win! <<<" << std::endl;
	         m1.showStats();
            break;
        }
        if (first_attack)
           goto last;

    first_dragon:
        m2.attack(m1);
        m1.showStats();
        if( m1.getHP() <= 0 ){
            std::cout << ">>> Dragon died, Unicorn win <<<" << std::endl;
	         m2.showStats();
            break;
        }
        if (first_attack)
           goto second_unicorn;
    last:
        std::cout << "===============================" << std::endl;
        cnt++;
    }
    return 0;
}

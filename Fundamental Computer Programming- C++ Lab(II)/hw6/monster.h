#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

class Monster {
    private:
        int HP;
        int MaxHP;
        int Attack;
        int Defense;
    public:
        Monster(int hp, int mxhp, int atk, int def):HP(hp),MaxHP(mxhp),Attack(atk),Defense(def){}
        void setHP(int hp){ HP = hp; }
        int getHP() const { return HP; }
        int getMaxHP() const { return MaxHP; }
        int getAttack() const { return Attack; }
        int getDefense() const { return Defense; }
        void showStats(){
            std::cout << std::setw(10) << "Monster(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl; 
        }
        void attack(Monster &m){
            m.setHP(m.getHP() - (getAttack() - m.getDefense()));
        }
};

class Dragon : public Monster {
   private:
      double Rate;
   public:
      Dragon(double rt): Rate(rt), Monster(30, 30, 5, 2){} //set the dragon hp, attack, defend
      
      void showStats() {
         std::cout << std::setw(10) << "Dragon(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
      }
      void attack(Monster& m) {

         double damage = (rand() % 10 + 1)*Rate;  //addition damage
         m.setHP(m.getHP() - (getAttack() - m.getDefense()) - damage);
      }
};

class Unicorn : public Monster {
   public:
      Unicorn(): Monster(50, 50, 6, 1) {}  //set the unicorn hp, attack, defend
      void showStats() {
         std::cout << std::setw(10) << "Unicorn(" << std::setw(3) << getHP() << " / " << std::setw(3) << getMaxHP() << " )" << std::endl;
      }
      void attack(Monster& m) {
         int probability[4] = { 0, 0, 1, 0 };

         int select = rand() % 4;
         if (probability[select] == 1) //decide double attack or not
            m.setHP(m.getHP() - (getAttack() - m.getDefense())*2);
         else
            m.setHP(m.getHP() - (getAttack() - m.getDefense()));
      }
};

#endif // MONSTER_H

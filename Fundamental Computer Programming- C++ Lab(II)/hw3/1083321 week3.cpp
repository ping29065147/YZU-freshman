#include "DeckCard.h"
#include "vector"
#include <time.h>
#include <math.h>


const string Card::suits[NumSuits] = { " 紅心 ",
" 方塊 ", " 黑桃 ", " 梅花 " };
const string Card::faces[NumFaces] = { "A", "2",
"3", "4", "5", "6", "7", "8", "9", "10","J", "Q",
"K" };


string Card::toString()
{
   string CardName = suits[suit] + " " + faces[face];

   return CardName;
}

DeckOfCards::DeckOfCards()
{
   for (int a = 0; a < 4; a++) {
      for (int b = 0; b < 13; b++) {
         deck.push_back(Card(b, a));   //初始化
         //cout << Card(b, a).toString() << endl;
      }
   }

}

void DeckOfCards::shuffle()
{
   srand(time(NULL));
   int x;

   for (int a = 0; a < deck.size(); a++) {
      currentCard = rand() % deck.size();  //隨機產生交換牌

      swap(deck[a], deck[currentCard]);  //交換
   }
   currentCard = 0;
}

Card& DeckOfCards::dealCard()
{

   return deck[currentCard++];
}

bool DeckOfCards::moreCards()
{

   if (currentCard < 52)
      return true;
   else
      return false;
}
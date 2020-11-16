// deal cards
#include "DeckCard.h"
using namespace std;
int main ()
{   
    DeckOfCards deck;
    deck.shuffle();
    while(deck.moreCards()){
        Card& c = deck.dealCard();   
        cout << c.toString() << endl;
    }
}

// define class Card and DeckOfCards
#ifndef DECKCARD_H
#define DECKCARD_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int NumSuits = 4;
const int NumFaces = 13;

class Card
{
    public:
        Card(int f,int s): face(f),suit(s){}
        string toString();
    private:
        int face,suit;
        static const string suits[NumSuits];
        static const string faces[NumFaces];
};

class DeckOfCards
{
    private:
        vector<Card> deck;
        int currentCard;

    public:
        DeckOfCards();
        void shuffle();
        Card& dealCard();
        bool moreCards();
};

#endif // DECKCARD_H

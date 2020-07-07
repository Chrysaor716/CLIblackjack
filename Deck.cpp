//#include <iostream> //TODO: TEMPORARY FOR DEBUGGING; REMOVE LATER

#include "Deck.h"

Card::Card() {}

Card::Card(string type, int index, int value) {
    mType = type;
    mIndex = index;
    mValue = value;
}

string Card::getType() {
    return mType;
}

int Card::getValue() {
    return mValue;
}

int Card::changeValue(int val) {
    mValue = val;
}

Card::~Card() {}

// ----------

Deck::Deck() {
    // Cards 2-10, 4 copies each
    for(int i = 0; i < 36; i++) {
        int val = (i % 9) + 2; // generates a value between 2 and 10 (inclusive)
        cards.push_back(Card(std::to_string(val), i, val));
    }
    // Aces
    for(int i = 36; i < 40; i++) {
        cards.push_back(Card("Ace", i, 11));
    }
    // King, Queen, Jack (face cards)
    for(int i = 40; i < 52; i++) {
        string type = "King";
        if(i % 3 == 0) type = "King";
        else if(i % 3 == 1) type = "Queen";
        else type = "Jack";
        cards.push_back(Card(type, i, 10));
    }
    // Optionally, adding Joker cards would go here
}

void Deck::shuffle() {
    /*
    // DEBUGGING:
    // TODO: REMOVE BELOW DEBUGGING CODE AND REPLACE WITH IMPLEMENTATION
    for(int i = 0; i < NUM_CARDS_IN_DECK; i++) {
        std::cout << "i: " << i << std::endl;
        std::cout << "card info:" << std::endl;
        std::cout << "type > " << cards[i].getType() << std::endl;
        std::cout << "value > " << cards[i].getValue() << std::endl;
        std::cout << "------------\n";
    }
    */
}

Deck::~Deck() {}


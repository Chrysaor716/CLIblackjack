#include <cstdlib> // for rand(), srand()
#include <ctime> // for time()
#include <utility> // for swap() (C++11) (use <algorithm> for C++98)

#include "Deck.h"

Card::Card() {}

Card::Card(string type, int index, int value) {
    mType = type;
    mIndex = index;
    mValue = value;
    // Optionally add suit here
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
        string type = "Jack";
        if(i % 3 == 0) type = "King";
        else if(i % 3 == 1) type = "Queen";
        else type = "Jack"; // note: this line is technically optional
        cards.push_back(Card(type, i, 10));
    }
    // Optionally, adding Joker cards would go here
}

void Deck::shuffle() {
    srand(time(nullptr)); // initialize seed for randomization based on clock
    // Goes through each index of deck and swaps its element with another
    //      randomly chosen card ranging from itself to the end of the deck.
    for(int i = 0; i < NUM_CARDS_IN_DECK; i++) {
        // Swap the current card with itself or any of the remaining cards in deck
        int randIdx = i + (rand() % (NUM_CARDS_IN_DECK - i));
        std::swap(cards[i], cards[randIdx]);
    }
}

Card Deck::draw() {
    Card card = cards.back();
    cards.pop_back(); // remove card from top of deck
    return card;
}

void Deck::returnCard(Card card) {
    cards.insert(cards.begin(), card);
}

Deck::~Deck() {}


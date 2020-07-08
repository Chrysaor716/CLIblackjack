#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

using std::string;

/*
 *  Class to represent a single card whose attributes include:
 *  - type (Ace, 2-10, King, Queen, Jack)
 *  - index (placement in deck)
 *  - value (its numeric value for the game)
 */
class Card {
public:
    Card(); // default constructor
    Card(string type, int index, int value); // init constructor
    string getType();
    int getValue();
    // In the case of Ace, its value can change between 11 and 1
    int changeValue(int val);
    ~Card();
private:
    string mType;
    int mIndex;
    int mValue;
};

#endif

// ----------

#ifndef DECK_H
#define DECK_H

/*
 *  Class responsible for managing cards in a deck.
 *  It initializes the deck set by creating Cards and also
 *  handles shuffling.
 */
class Deck {
public:
    // Creates Cards and initializes deck
    Deck();
    // Shuffles deck
    void shuffle();
    // Draws a card from the top of the deck
    Card draw();
    // Returns card to deck
    void returnCard(Card card);
    ~Deck();
private:
    static const int NUM_CARDS_IN_DECK = 52;
    std::vector<Card> cards;
};

#endif

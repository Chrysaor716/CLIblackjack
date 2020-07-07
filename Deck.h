#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

using std::string;

class Card {
public:
    Card();
    Card(string type, int index, int value);
    string getType();
    int getValue();
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

class Deck {
public:
    Deck();
    void shuffle();
    ~Deck();
private:
    static const int NUM_CARDS_IN_DECK = 52;
    std::vector<Card> cards;
};

#endif

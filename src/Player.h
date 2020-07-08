#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_set>
#include <vector>

#include "Deck.h" // includes Card class

/*
 *  Base Player class that contains general attributes for
 *  players of the game.
 */
class Player {
public:
    // Default constructor
    Player();
    // Returns sum of card values in hand
    int getHandTotal();
    // On the occassion a card's value changes (particularly Aces), change hand's total;
    //      only occurs when an Ace is present in hand
    void updateHandTotal();
    // Adds a card to player's hand and updates total
    void addToHand(Card card);
    // Returns number of cards in hand; used for inserting Ace indicies
    int getHandSize();
    // Adds Ace card index to set
    void addAce(int idx);
    // Tells the game whether or not Player has a soft Ace (value 11) in hand
    bool hasSoftAce();
    // Deletes all cards from hand (done after returning cards to deck)
    void clearHand();
    // Shows Player's hand. Dealt differently depending on whether the Player is the
    //      user or dealer.
    virtual void showHand() = 0;
    // Returns hand to deck; dealer has wildcard not part of hand vector
    virtual std::vector<Card> getHand() = 0;
    // Destructor
    ~Player();
protected:
    // The cards in player's hand
    std::vector<Card> hand;
    // Keeps track of soft Ace (value 11) placements in hand
    std::unordered_set<int> aces;
    // Sum of values in hand
    int handTotal;
};

#endif

// ----------

#ifndef USER_H
#define USER_H

class User : public Player {
public:
    User();
    void showHand();
    std::vector<Card> getHand();
    void addWin();
    int getWinPercentage(int numRounds);
    ~User();
private:
    int roundsWon;
};

#endif

// ----------

#ifndef DEALER_H
#define DEALER_H

class Dealer : public Player {
public:
    Dealer();
    void showHand();
    std::vector<Card> getHand();
    void setWildcard(Card card);
    Card getWildcard();
    ~Dealer();
private:
    // Determines if it is currently the dealer's turn and if the wildcard
    //      should be revealed
    bool inTurn;
    // Dealer has hidden card that is revealed and summed later
    Card wildcard;
};

#endif

#include <iostream> // for cout
#include "Player.h"

using std::cout;
using std::endl;

Player::Player() : handTotal(0) {}

int Player::getHandTotal() {
    return handTotal;
}

void Player::toggleAce() {
    // Change any existing Ace's value to a 1
    auto it = aces.begin(); // get an Ace index in hand
    hand[*it].changeValue(1); // change to hard value
    aces.erase(it); // remove hard ace from list

    // Subtract 10 from hand total since an 11 changed to a 1
    handTotal -= 10;
}

void Player::addToHand(Card card) {
    hand.push_back(card);
    handTotal += card.getValue();
    // Automatically add Aces to Ace set since it starts off soft (11);
    //      hand total is evaluated later and Ace is toggled when need be
    if(card.getType() == "Ace")
        aces.insert(hand.size() - 1);
}

bool Player::hasSoftAce() {
    // If set is not empty, it contains a soft Ace
    return (!aces.empty());
}

bool Player::bust() {
    // If there are any soft Aces in hand, downsize them
    if(hasSoftAce())
        toggleAce();
    // Player has busted if over 21 at this point
    if(handTotal > 21)
        return true;
    return false;
}

void Player::clearHand() {
    hand.clear();
    handTotal = 0;
    // Reset Aces set as well
    aces.clear();
}

Player::~Player() {}

// ----------

User::User() : roundsWon(0) {}

void User::showHand() {
    cout << "____________________\n\n";
    cout << "Your hand\n";
    cout << "| ";
    // Display card type and its value
    for(auto card : hand) {
        cout << card.getType() << "(" << card.getValue()
             << ")" << " | ";
    }
    cout << "\nYour sum = " << handTotal << endl;
    cout << "____________________\n";
}

std::vector<Card> User::getHand() {
    return hand;
}

void User::addWin() {
    roundsWon++;





//TODO REMOVE
cout << "-------- rounds won >>>>>>" << roundsWon << "\n";





}

int User::getWinPercentage(int numRounds) {
    return (roundsWon / numRounds) * 100;




//TODO REMOVE
cout << "-------- rounds won (WP) >>>>>>" << roundsWon << "\n";




}

User::~User() {}

// ----------

Dealer::Dealer() : inTurn(false) {}

void Dealer::setTurn(bool isInTurn) {
    inTurn = isInTurn; // Flag for showHand() display/output
    if(inTurn == true) {
        addToHand(wildcard); // include wildcard to dealer's hand
        wildcard = Card(); // clear wildcard slot
    }
}

void Dealer::showHand() {
    cout << "____________________\n\n";
    cout << "Dealer's hand\n";
    // Display from the first card or second card depending
    //      on whether or not it is currently the dealer's turn
    if(inTurn) {
        cout << "| ";
    } else {
        // If not in turn, display question mark for face-down card
        cout << "| ? | ";
    }
    for(auto card : hand) {
        cout << card.getType() << "(" << card.getValue()
             << ")" << " | ";
    }
    cout << "\nDealer's sum = " << handTotal << endl;
    cout << "____________________\n";
}

std::vector<Card> Dealer::getHand() {
    // Add wildcard to hand (if valid)
    // Need this check if wildcard has already been added to dealer's hand
    if(wildcard.getType() != "")
        hand.push_back(wildcard);
    wildcard = Card(); // clear wildcard slot
    return hand;
}

void Dealer::setWildcard(Card card) {
    wildcard = card;
}

Card Dealer::getWildcard() {
    return wildcard;
}

Dealer::~Dealer() {}

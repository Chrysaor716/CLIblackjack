#include <iostream> // for cout
#include "Player.h"

using std::cout;
using std::endl;

Player::Player() : handTotal(0) {}

int Player::getHandTotal() {
    return handTotal;
}

void Player::updateHandTotal() {
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
}

int Player::getHandSize() {
    return hand.size();
}

void Player::addAce(int idx) {
    aces.insert(idx);
}

bool Player::hasSoftAce() {
    // If set is not empty, it contains a soft Ace
    return (!aces.empty());
}

void Player::clearHand() {
    hand.clear();
    handTotal = 0;
}

Player::~Player() {}

// ----------

User::User() : roundsWon(0) {}

void User::showHand() {
    cout << "Your hand\n";
    cout << "| ";
    for(auto card : hand) {
        cout << card.getType() << " | ";
    }
    cout << "\nYour sum = " << handTotal << endl;
}

std::vector<Card> User::getHand() {
    return hand;
}

void User::addWin() {
    roundsWon++;
}

int User::getWinPercentage(int numRounds) {
    return (roundsWon / numRounds) * 100;
}

User::~User() {}

// ----------

Dealer::Dealer() : inTurn(false) {}

void Dealer::showHand() {
    cout << "Dealer's hand\n";
    // Display from the first card or second card depending
    //      on whether or not it is currently the dealer's turn
    if(inTurn) {
        // If in turn, show all cards from the beginning
        cout << "| ";
    } else {
        // If not in turn, display question mark for face-down card
        cout << "| ? | ";
    }
    for(auto card : hand) {
        cout << card.getType() << " | ";
    }
    cout << "\nDealer's sum = " << handTotal << endl;
}

std::vector<Card> Dealer::getHand() {
    // Add wildcard to hand to return hand set to deck
    hand.push_back(wildcard);
    wildcard = Card(); // clear wildcard
}

void Dealer::setWildcard(Card card) {
    wildcard = card;
}

Card Dealer::getWildcard() {
    return wildcard;
}

Dealer::~Dealer() {}

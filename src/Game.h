#ifndef GAME_H
#define GAME_H

#include "Player.h" // contains User and Dealer child classes as well
#include "Deck.h"

/*
 *  Controls the flow of the game (player's turns, shuffling deck every 6 rounds, etc.).
 */
class Game {
public:
    Game();
    // Main fuction checks status to determine whether to terminate program
    int getExitStatus();
    // Prompts user whether to start a new round
    void pending();
    // Deals cards to Players' hands
    void deal();
    void userTurn();
    void dealerTurn();
    ~Game();
private:
    User user; // note that this can be an array instead if there are more players
    Dealer dealer;

    int exitStatus; // Determines whether to end the game
    int round;
    Deck deck;
};

#endif
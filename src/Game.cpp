#include <iostream> // for cin, cout

#include "Game.h"

using std::cin;
using std::cout;
using std::endl;

Game::Game() {
    exitStatus = false;
    round = 0;
    //deck.shuffle(); // Note: this is technically optional since it shuffles at the beginning anyway
    // Print intro info at start (optionally put this into separate helper function)
    cout << "__________________\n";
    cout << "|    BLACKJACK    |\n";
    cout << "Please refer to README for rules\n";
}

int Game::getExitStatus() {
    return exitStatus;
}

void Game::pending() {
    // Return cards in hand to deck, if any
    if(user.getHandSize() > 0) {
        for(auto card : user.getHand()) {
            // Return each card back to bottom of deck
            deck.returnCard(card);
        }
        user.clearHand();
    }
    if(dealer.getHandSize() > 0) {
        for(auto card : dealer.getHand()) {
            deck.returnCard(card);
        }
        dealer.clearHand();
    }

    if(round % 6 == 0) 
        deck.shuffle();

    cout << "Start a new round? (y/n)\n";
    cout << "Rounds played: " << round << endl;
    // Print win percentage info if user has played at least 1 round
    if(round) cout << "Current win percentage: " << user.getWinPercentage(round) << endl;
    cout << "> ";
    string input;
    // Loop infinitely until user gives input to start or end game
    while(1) {
        // Stretch goal: add regex to include variations of "yes" and "no" strings
        cin >> input;
        if(input == "y" || input == "Y") {
            round++;
            deal();
        } else if(input == "n" || input == "N") {
            cout << "Exiting...\n";
            // TODO: exit program from here instead and change main function
            exitStatus = true; // send exit status to main function
            break;
        } else {
            cout << "Invalid input! Please enter 'y' or 'n': ";
        }
    }
}

void Game::deal() {
    // Draw cards from top of deck and add to players' hands.
    // Note that we can use a variable instead for variable number
    //      of players, but in this case, we always deal 4 cards
    //      (2 for user player and 2 for dealer).
    // This loop alternates drawing a card to the user and dealer
    //      by checking if iteration is even or odd.
    cout << "\nDealing cards...\n";
    // Deal first 3 cards normally
    Card card;
    for(int i = 0; i < 3; i++) {
        // Removes top card from deck
        card = deck.draw();
        if(i%2 == 0) {
            user.addToHand(card);
            // If card was an Ace, add to Ace set
            if(card.getType() == "Ace") {
                // Ace inserted into hand was most recent index
                user.addAce(user.getHandSize() - 1);
            }
        } else {
            dealer.addToHand(card);
            // If an Ace was dealt to the dealer, add to dealer's Ace set
            if(card.getType() == "Ace") {
                dealer.addAce(dealer.getHandSize() - 1);
            }
        }
    }
    // Make 4th card the dealer's hidden card
    dealer.setWildcard(deck.draw()); //TODO: need to consider if it's an Ace later on when card is revealed

    // Display the existing hands
    user.showHand();
    dealer.showHand();

    // User player moves first
    userTurn();
}

void Game::userTurn() {
    // User automatically wins the round if drawn a 21 at the start.
    if(user.getHandTotal() == 21) {
        cout << "\n====================\n";
        cout << "Blackjack! You win!\n";
        cout << "\n====================\n";
        user.addWin();
        pending(); // prompt user to play again
    } else {
        if(user.getHandTotal() > 21) {
            // Check if total is hard or soft
            if(user.hasSoftAce()) {
                //TODO: remove below placeholder and replace with real code
                cout << "Has soft ace\n";
            }
        }
        // TODO: see state diagram & rules to continue game logic here
    }
}

void Game::dealerTurn() {}

Game::~Game() {
    exitStatus = true;
    round = 0;
}

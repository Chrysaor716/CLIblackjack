#include <iostream> // for cin, cout

#include "Game.h"

using std::cin;
using std::cout;
using std::endl;

Game::Game() {
    round = 0;
    //deck.shuffle(); // Note: this is technically optional since it shuffles at the beginning anyway
    // Print intro info at start (optionally put this into separate helper function)
    cout << "|    BLACKJACK    |\n";
    cout << "Please refer to README for rules\n";
}

void Game::pending() {
    // Return cards in hands to deck, if any
    if(!user.getHand().empty()) {
        for(auto card : user.getHand()) {
            // Return each card back to bottom of deck
            deck.returnCard(card);
        }
        user.clearHand();
        // Alternatively, one could iteratively pop cards from hand and add to bottom of deck
        //      (more "realistic") instead of "copying" the hand and clearing the hand
    }
    if(!dealer.getHand().empty()) {
        for(auto card : dealer.getHand()) {
            deck.returnCard(card);
        }
        dealer.clearHand();
    }
    // Dealer is not in turn at this stage
    dealer.setTurn(false);

    if(round % 6 == 0) { 
        cout << "---> Shuffling...\n";
        deck.shuffle();
    }

    cout << "Start a new round? (y/n)\n";
    cout << "> Rounds played: " << round << endl;
    // Print win percentage info if user has played at least 1 round
    if(round) cout << "> Current win rate: " << user.getWinPercentage(round) << "%\n";
    cout << "> ";
    string in;
    cin >> in;
    // Loop infinitely until user gives valid input to start or end game
    // Stretch goal: add regex to include variations of "yes" and "no" strings
    while(in != "y" && in != "Y" && in != "n" && in != "N") {
        cout << "Invalid input! Please enter 'y' or 'n': ";
        cin >> in;
    }
    if(in == "y" || in == "Y") {
        round++;
        deal();
    }
    // If user entered "No", return and terminate program (zero indicates successful completion)
    exit(0);
}

void Game::deal() {
    // Draw cards from top of deck and add to players' hands.
    // Note that we can use a variable instead for variable number
    //      of players, but in this case, we always deal 4 cards
    //      (2 for user player and 2 for dealer).
    // This loop alternates drawing a card to the user and dealer
    //      by checking if iteration is even or odd.
    cout << "\nDealing cards...\n\n";
    // Deal first 3 cards normally
    for(int i = 0; i < 3; i++) {
        if(i%2 == 0)
            user.addToHand(deck.draw());
        else
            dealer.addToHand(deck.draw());
    }
    // Make 4th card the dealer's hidden card
    // Note that technically we can draw the dealer's 2nd card once
    //      it becomes the dealer's turn, since it's "random", but
    //      this is to simply make the drawing more realistic
    dealer.setWildcard(deck.draw());

    // Display the existing hands
    user.showHand();
    dealer.showHand();

    // User player moves first
    userTurn();
}

void Game::userTurn() {
    // User automatically wins the round if drawn a 21 at the start.
    if(user.getHandTotal() == 21) {
        cout << "\n===================\n";
        cout << "\nBlackjack! You win!\n";
        cout << "\n===================\n";
        user.addWin();
        pending(); // prompt user to play again
    } else {
    // If it's not 21, this state can go 3 routes:
    // - User hits: draw a card and add to hand total
    // - User stands: holds total and move to dealer's turn
    // - User busts: hand total exceeds 21 and user loses the round
    //               (happens after hitting)
        string input;
        hitOrStand(input);
        // User chooses to hit
        while(input == "h" || input == "H") {
            cout << "You hit!\n";
            user.addToHand(deck.draw());
            if(user.getHandTotal() > 21) {
                // Checks if there are any hard Aces to downsize
                if(user.bust()) {
                    user.showHand();
                    cout << "\n===================\n";
                    cout << "\n Bust! You lose :(\n";
                    cout << "\n===================\n";
                    pending(); // prompt user to play another round
                }
            }
            user.showHand();
            //dealer.showHand(); //show dealer's hand alongside user's
            // If user is at exactly 21, move on to dealer's turn
            if(user.getHandTotal() == 21) {
                cout << "---> 21! Your turn automatically ends. Dealer's turn...\n"; // let user know their turn has ended
                dealerTurn();
            }
            // Else, if user hasn't busted yet, ask to continue hitting or stand
            hitOrStand(input);
        }
        // Player is done hitting and hasn't busted; move to dealer
        dealerTurn();
    }
}

void Game::dealerTurn() {
    cout << "Dealer moving...\n";
    dealer.setTurn(true); // adds wildcard to dealer's hand and sum
    //user.showHand(); // show user's hand alongside dealer's hand
    dealer.showHand(); // reveal wildcard

    // At dealer's turn:
    // - They must hit until their total is 17+
    // - If they hit 17 with a soft Ace, they must hit again
    // - If they bust, user wins
    // - Once the dealer reaches a total of 17 or higher, they must hold

    // Draw while less than 17 or at hard 17
    // Optionally add a "sleep" or "wait" timer in between dealer hits to slow down
    //      console outputs and dispay each step more explicitly
    while(dealer.getHandTotal() < 17 || (dealer.getHandTotal() == 17 && dealer.hasSoftAce())) {
        // Hit while less than 17
        cout << "Dealer hits.\n";
        dealer.addToHand(deck.draw());

        // If dealer busts at any point while hitting, dealer loses
        // This check also downsizes any soft Aces if they exist
        if(dealer.bust()) {
            // Show dealer's hand & bust message
            dealer.showHand();
            cout << "\n========================\n";
            cout << "\n Dealer busted! You win!\n";
            cout << "\n========================\n";
            user.addWin();
            pending(); // prompt user to play again
        }
        
        dealer.showHand();
    }
    // By this point, dealer is at hard 17 or a value greater than 17
    // Check if they've busted
    if(dealer.bust()) {
        // Show dealer's hand & bust message
        dealer.showHand();
        cout << "\n========================\n";
        cout << "\n Dealer busted! You win!\n";
        cout << "\n========================\n";
        user.addWin();
        pending(); // prompt user to play again
    }

    // If they're still at 21 and under, compare
    compare();
}

void Game::hitOrStand(string &input) {
    cout << "What would you like to do?\n"
         << "Press 'h' to hit (draw a card).\n"
         << "Press 's' to stand (hold total).\n"
         << "> ";
    cin >> input;
    // Loop indefinitely until user enters valid input
    // Optional: allow user to quit game here (mid-game)
    while(input != "h" && input != "H" && input != "s" && input != "S") {
        cout << "Invalid input! Please enter 'h' or 's': ";
        cin >> input;
    }
}

void Game::compare() {
    if(user.getHandTotal() == dealer.getHandTotal()) {
        cout << "\n===============\n";
        cout << "\n     TIE!\n";
        cout << "\n===============\n";
    } else if(user.getHandTotal() > dealer.getHandTotal()) {
        cout << "\n===============\n";
        cout << " \n You win!!\n";
        cout << "\n===============\n";
        user.addWin();
    } else {
        cout << "\n===============\n";
        cout << "  \nDealer wins!\n";
        cout << "\n===============\n";
    }
    pending(); // prompt user to play again
}

Game::~Game() {
    round = 0;
}

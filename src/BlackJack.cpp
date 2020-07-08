#include "Game.h"

int main() {
    Game game;
    // Start game loop
    game.pending();

    // Loop until user ends game
    while(1) {
        if(game.getExitStatus())
            return 0;
        else
            continue;
    }

    return 0;
}

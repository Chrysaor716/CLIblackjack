# Supplementary docs detailing the process

### Basics
With little to no knowledge of the game blackjack and what a standard deck of playing card entails, I had to first learn:
1. The rules of blackjack (outlined in README)
2. What a deck of cards for the game contains and some of the terminologies:
    - Ace (4)
    - 2-10 (4x9 = 36)
    - Jack (4)
    - Queen (4)
    - King (4)
    - 4 + 36 + 4 + 4 + 4 = 52 total cards
    - Optional: Joker (2) (unused in blackjack)
    - Each card has 4 suits: heart, diamond, spades, and clubs. These "suits" are irrelevant in blackjack; only the value matters.
    - "Face cards" = King, Queen, Jack
    - "Hand" = the set of cards a player is holding

After learning the rules and gaining some familiarity with a standard stack of playing cards, a state diagram was drawn, as well as an outline of classes (listed below under the [Classes](#classes) section), prior to jumping into code.

### CLI or GUI?
**CLI**:
- (+) Simpler (better under time constraints or for short-term/smaller projects)
- (-) Less "user-friendly" (not a problem for this project since it's not being delivered to the general public)
- (+) Draws focus away from aesthetics (which is an unnecessary detail for the scope of this project)
**GUI**:
- (+) More user-friendy
- (+) More aesthetic
- (-) More bloated code
- (-) Need to spend extra time learning libraries, APIs

The pros/cons can be arguable, but were what I considered pros/cons for the purpose and scope of this project.

The game seemed simple enough such that implementing a UI might be unnecessary extra work (unless the UI was simple and can be done quickly, but for me, I'd have to invest some extra time learning libraries). For that reason, I chose to to do a CLI program so that I could just focus on the game flow and logic and worry less about "bloat" code and wrappers. Adding a GUI could also be a stretch goal if I wanted to add more to the game down the road. Of course, naturally, if delivered to the "general" public, it'd make more sense to put the game into a UI, but here, we can pretend it is a program that can be packaged with a Linux distribution that developers will open on their terminal in between breaks!  

(Side tangent: Did you know you can run `man man`?)

### Implementing the game
After reading the rules and specifications, prior to writing any code, a state machine was drawn to get a better picture of the game flow:
![Digital copy (originally drawn by hand on scrap paper)](blackjack_state_machine.png "Blackjack State Machine")  
This model was frequently referenced during implementation.

Ace has a value of 1 (hard) or 11 (soft).
- Its value is 11 until the hand goes over 21, then it becomes 1 to avoid busting.

Since the requirement is merely to keep track of win percentage, there is no need to implement betting rules and keep track of the player's/dealer's money bank. This can be a stretch goal.

Shuffling: There are various shuffling algorithms, but the easiest way was to simply iterate through the deck and swap the current card with any of the remaining cards in the deck ranging from itself to the end of the deck.

Regarding the project directory structure, makefile, and source control: the project is small enough that these are not as big a deal, but would obviously require more organization and improvements with larger-scale projects.

A brief description of class functions are provided in the header files (much like if one would read through an API). Comments contain descriptions of functionalities, as well as possible alternative solutions.

In terms of program and game flow: `pending` is the "return point" from every state in the game. It simply calls `exit()` to terminate the program when the user is done playing as there was too much management in keeping track of the call stack as more states were implemented making a call to `pending` (one could also write the program such that it returns from the current state, pops from the call stack, and return to `pending`; however, again, it's more management in keeping track of the program flow). That said, it's worth noting that the program doesn't terminate from `main` but rather from `pending` because of the exit function, but is effectively the same as returning from `main`.

### Classes
- Player
    - Base class for User and Dealer
    - Contains attributes that the User and Dealer have in common

    - User : Player
        - Inherits Player
        - Win percentage
    - Dealer : Player
        - Inherits Player
        - Contains "wildcard" (initially faced down)

- Card
    - string type
    - int index (placement in deck)
    - int value
    - (optional: string suit)

- Deck
    - Initializes cards to create standard deck
    - Handles card shuffling
    - Handles card drawing
    - Adds card to deck when cards are being returned from Players' hands
    - Ideally, can use more than one deck in other modes
    - (optional: contains Jokers)

- Game
    - Manages game flow (modelled after the state machine diagram)
    - Shuffles deck every 6 rounds
    - Interface with user player
    - Auto-plays dealer rounds

#### General future Improvements & features
- Unit tests
- UI wrapper!
    - possibly qt
- Possibly a separate class for print statements (if keeping as a CLI program)
    - can improve program visually
    - also helps see AI moves better or make each step more visually explicit
- Possible configuration files for debug mode?
- Add money bank
- Possible multiplayer mode
- Allow multiple decks
- regex for more robust inputs
- Possible quit option at every state so that the user can exit (gracefully) at any point in game
- Possibly "more randomized" shuffle algorithm?

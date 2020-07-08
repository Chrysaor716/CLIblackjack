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

After learning the rules and gaining some familiarity with a standard stack of playing cards, a state diagram was drawn, as well as an outline of classes (listed below under the **Classes** section), prior to jumping into code.

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
The game seemed simple enough such that implementing a UI might be unnecessary extra work (unless the UI was simple and can be done quickly, but for me, I'd have to invest some extra time libraries). For that reason, I chose to to do a CLI program so that I could just focus on the game flow and logic and worry less about "bloat" code and wrappers. Adding a GUI could also be a stretch goal if I wanted to add more to the game down the road.

### Implementing the game
Ace has a value of 1 (hard) or 11 (soft).
- Its value is 11 until the hand goes over 21, then it becomes 1 to avoid busting.

Since the requirement is merely to keep track of win percentage, there is no need to implement betting rules and keep track of the player's/dealer's money bank. This can be a stretch goal.

Shuffling: There are various shuffling algorithms, but the easiest way was to simply iterate through the deck and swap the current card with any of the remaining cards in the deck ranging from itself to the end of the deck.

Regarding the project directory structure, makefile, and commits: the project is small enough that these are not as big a deal, but would obviously require more organization and improvements with larger-scale projects.

### Classes
- Player
    - Base class for User and Dealer

    - User : Player
        - Inherits Player
        - Win percentage
    - Dealer : Player
        - Inherits Player
        - Contains "wildcard"

- Card
    - string type
    - int index (placement in deck)
    - int value

- Deck
    - Initializes cards to create standard deck
    - Handles card shuffling
    - Handles card drawing
    - Ideally, can use more than one deck in other modes

- Game
    - Keeps track of game state
    - Shuffles deck every 6 rounds
    - Interface with user player

# Command line blackjack

### Compiling and running:

### Rules
The goal is to beat the dealer's hand without going over 21.
- Face cards (King, Queen, Jack) have a value of 10.
- Ace has a value of 1 (hard) or 11 (soft).
- Numbered cards are its respective values (2 is 2, 3 is 3, etc.).
- In this version, there is only the player and the dealer (CPU).
- The player starts with 2 cards, both revealed.
- The dealer starts with 2 cards, one revealed and one hidden.
- In each round, the player can:
    - "Hit" = draw another card from deck.
    - "Stand" = hold total in hand and end turn.
- If you are dealt 21 from the start (10 and Ace), you get a blackjack! This means you automatically win the round.
- A "bust" happens when your hand goes over 21. In this case, the dealer wins regardless of their hand.
- Once the player ends their turn, the dealer reveals the hidden card and then can also choose to hit until they stand.
- Dealer will hit until their total is 17 or higher.
- If the dealer goes over 21 (bust), the player wins the round.
- If the player's hand equals the dealer's hand, then it is a tie.

#### Additional requirements:
- Dealer must hit on soft 17.
    - A soft hand is a hand that contains an Ace counted as 11.
    - The hand is hard otherwise (it has no Aces or contains one or more Ace that all count as 1).
- Single deck. The deck is shuffled every 6 rounds.
- Player is not allowed to split cards.
- Keep track of win percentage for player.


## Card Game with Blowfish Encryption

This GitHub repository contains a card game implementation written in C. The card game deals with a shuffled deck of cards and determines the winning player based on specific conditions. Additionally, the deck file is encrypted using the Blowfish encryption algorithm.

### Features

- Reads a file with a shuffled deck of cards
- Deals cards to 4 players until one of the players obtains 4 cards of the same value
- Determines the winning player based on the specified rules
- Prints the winning player and their cards in descending order
- Encrypts the deck file using the Blowfish algorithm for enhanced security

### Gameplay

1. Enter the encrypted file name to open.
2. The game starts with 4 players, each having an empty array of cards.
3. One card is dealt to each player in each turn until a player collects 4 cards of the same value.
4. If multiple players achieve this on the same turn, the winner is determined based on the higher value of the cards forming the four.
5. If no player wins when the deck is exhausted, the winner is the player with the highest total card value.
6. In case of multiple players with the same maximum total, the winner is the player with stronger suits.
7. At the end of the game, the winning player's cards are printed as ordered pairs of (value, suit) in descending order.

### Encryption

The deck file encryption is implemented using the Blowfish encryption algorithm. The encryption process ensures the confidentiality and integrity of the deck contents. The encrypted file is read during gameplay and decrypted for processing. The encryption and decryption processes are handled using the Blowfish algorithm.

### Usage

To run the card game with Blowfish encryption, follow these steps:

1. Clone this GitHub repository to your local machine.
2. Compile the C code, ensuring that the Blowfish library and dependencies are correctly linked.
3. Execute the compiled program, providing the encrypted deck file name as an input.
4. Follow the instructions displayed to play the game.
5. The winning player and their cards will be printed as the output.

Note: Make sure to use the correct Blowfish encryption key to decrypt the deck file before playing the game.

Feel free to contribute to this repository by enhancing the game mechanics, improving encryption features, or adding new functionalities.

Enjoy the card game and have a great time!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PLAYERS 4
#define NUM_CARDS 52
#define MAX_CARDS_PER_PLAYER 13
#define MAX_CARD_VALUE 20

struct Card {
    int value;
    char suit;
};

struct Player {
    struct Card hand[MAX_CARDS_PER_PLAYER];
    int numCards;
};

//comparison function for sorting cards
int compareCards(const void *a, const void *b) {
    const struct Card *cardA = (const struct Card *)a;
    const struct Card *cardB = (const struct Card *)b;

    if (cardA->value != cardB->value) {
        return cardA->value - cardB->value;
    } else {
        return strcmp (cardA->suit - cardB->suit);
    }
}

int main() {
    struct Player players[NUM_PLAYERS];
    struct Card deck[NUM_CARDS];
    char filename[100];
    FILE *file;
    int winner = -1;
    int turn = 0;
    int i, j;

    printf("Enter a file name to open: ");
    scanf("%s", filename);
    
    //open the file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    //initialize the players hand count
    for (i = 0; i < NUM_PLAYERS; i++) {
        players[i].numCards = 0;
    }
    
    //read card values from the file into the deck
    for (i = 0; i < NUM_CARDS; i++) {
        char value[3];
        fscanf(file, "%s %c", value, &deck[i].suit);
        deck[i].value = atoi(value);
    }
    fclose(file);

    //loop to continue until a winner is found and all cards are played
    while (winner == -1 && turn < NUM_CARDS) {
        struct Card currentCard = deck[turn];
        struct Player *currentPlayer = &players[turn % NUM_PLAYERS];
        currentPlayer->hand[currentPlayer->numCards] = currentCard;
        currentPlayer->numCards++;
         
        //checks if the current player has 4 cards that are the same
        if (currentPlayer->numCards >= 4) {
          qsort(currentPlayer->hand, currentPlayer->numCards, sizeof(struct Card), compareCards);

            for (i = 0; i <= currentPlayer->numCards - 4; i++) {
              if (currentPlayer->hand[i].value == currentPlayer->hand[i + 3].value) {
                winner = turn % NUM_PLAYERS;
                break;
                }
            }
        }

        turn++;
    }
    
    //if no winner is found after all cards are played determine the winner based on the highest total/suit strength
    if (winner == -1) {
        int maxTotal = -1;
        int maxSuitStrength = -1;

          for (i = 0; i < NUM_PLAYERS; i++) {
            struct Player *currentPlayer = &players[i];
            int total = 0;
            int suitStrength = -1;
            
            // calculate the total value of the hand and the highest suit
            for (j = 0; j < currentPlayer->numCards; j++) {
                total += currentPlayer->hand[j].value;
                if (currentPlayer->hand[j].suit > suitStrength) {
                    suitStrength = currentPlayer->hand[j].suit;
                }
            }
            
            //update the winner if the current player has higher total and suit strenght than the previous
            if (total > maxTotal || (total == maxTotal && suitStrength > maxSuitStrength)) {
                winner = i;
                maxTotal = total;
                maxSuitStrength = suitStrength;
            }
        }
    }
    
    //print the winning player or no winner in some cases
    if (winner != -1) {
        printf("Player %d wins: ", winner + 1);

        struct Player *winningPlayer = &players[winner];
          for (i = 0; i < winningPlayer->numCards; i++) {
          printf("(%d, %c) ", winningPlayer->hand[i].value, winningPlayer->hand[i].suit);
    }
          printf("\n");
    } else {
        printf("No winner.\n");
    }

    return 0;
}

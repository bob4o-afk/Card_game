#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#include "blowfish.h"
#include "karti.h"

#define MAX_FILENAME_LENGTH 100

int main() {
  const char *input_file = "karti.txt";
  const char *encrypted_file = "encrypted_file.txt";
  const char *decrypted_file = "decrypted_file.txt";
  char* key = NULL;
  size_t key_length = 0;

  printf("Enter the encryption key: ");
  getline(&key, &key_length, stdin);
  key[strcspn(key, "\n")] = '\0';

  encrypt_file(input_file, encrypted_file, key);
  decrypt_file(encrypted_file, decrypted_file, key);

  struct Player players[NUM_PLAYERS];
  struct Card deck[NUM_CARDS];
  char filename[100];
  FILE *file;
  int winner = -1;
  int turn = 0;
  int i, j;

  printf("Enter a file name to open: ");
  scanf("%s", filename);  //Enter either "karti.txt" or "decrypted_file.txt"
  
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


  free(key);
  return 0;
}

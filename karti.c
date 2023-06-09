#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "karti.h"



//comparison function for sorting cards
int compareCards(const void *a, const void *b) {
    const struct Card *cardA = (const struct Card *)a;
    const struct Card *cardB = (const struct Card *)b;

   if (cardA->value != cardB->value) {
        return cardA->value - cardB->value;
    } else {
        return cardA->suit - cardB->suit;
    }
}


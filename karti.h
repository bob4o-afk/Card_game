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

int compareCards(const void *a, const void *b);
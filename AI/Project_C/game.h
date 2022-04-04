// personal header files
#include "Data_type.h"
#include "Card_Function.h"
//#include "Keyboard.h"

/* PARAMETERS */
// keycodes used for game
#define KEY_SPACE 0x29
#define KEY_ENTER1 0x5A
#define KEY_ENTER2 0xE05A
#define KEY_UP 0xE075
#define KEY_DOWN 0xE072
#define KEY_LEFT 0xE06B
#define KEY_RIGHT 0xE074

// time limit
#define TIME_LIMIT_CHOOSE_CARD 30000

#ifndef _GAMEH_
#define _GAMEH_

/* FUNCTION DEFINITION */
struct player* playerInit(int playerID);
struct card* cardInit(int playerID);
void ultimateInit(struct player* players);
void cardFunction(struct player* player, int card_ID, int buff_ID);
int chooseCard(struct player* currPlayer);
// int getCardFromKbd();

/* FUNCTION IMPLEMENTATION */
/* Game initialization functions */

struct player* playerInit(int playerID) {
    struct player* player = malloc(sizeof(struct player));

    player->cards = cardInit(playerID);
    player->player_ID = playerID;
    player->health = 20;
    player->shield[0] = 0;
    player->shield[1] = 0;
    player->shield[2] = 0;
    player->indexAdd = 0;
    player->indexRemove = 1;
    player->time_limit = 0;
    player->alive = true;

    return player;
}

struct card* cardInit(int playerID){
    // array of cards
    struct card* card_array = malloc((card_num + 1) * sizeof(struct card));

    for (int i = 0; i < card_num; i++){
        card_array[i].card_ID = i; // index
        card_array[i].player_ID = playerID;
        card_array[i].valid = true; // set card to valid
    }

    return card_array;
}

void ultimateInit(struct player* player){
    // I don't know why this doesnt show... ***
    FILE* file = fopen("C:\\Users\\23612\\Documents\\CPEN_391\\Module_2\\l2c-39\\AI\\Project_C\\ult_description.txt", "r");
    int c;

    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }

    srand(time(NULL));
    player->ultimate = rand() % ult_num;

    if (player->ultimate == 2){
        player->health = 30;
    }

    printf("Player%d received ultimate %d!\n", player->player_ID, player->ultimate);

}

void cardFunction(struct player* player, int card_ID, int buff_ID){
    // if player has round buff 2, attack point doubled
    int attack_card_multiplier = buff_ID == 2 ? 2 : 1;
    int shield_multiplier = buff_ID == 1 ? 2 : 1;

    // card from 0-6 is attack, 7-12 is defence
    if (card_ID <= 6){
        card_simple_attack(((card_ID+1) * attack_card_multiplier), player);
    } else {
        card_simple_defence(((card_ID-6) * shield_multiplier), player);
    }
}

/* Functions for rounds */
int chooseCard(struct player* currPlayer) {
    // Draw 3 cards from deck
    int cardOnTable[3];
    int numDrew = 0;

    srand(time(NULL));

    while (numDrew < 3) {
        // get random value between 0 and 12
        int randCard = rand() % card_num;
        // if current player has not used cards[randCard] before put it on table
        if (currPlayer->cards[randCard].valid == true) {
            cardOnTable[numDrew] = currPlayer->cards[randCard].card_ID;
            currPlayer->cards[randCard].valid = false;
            
            numDrew++; // increment number of cards on table
        }
    }

    printf("card on table for player %d\n", currPlayer->player_ID);
    for (int i = 0; i < 3; i++) {
        printf("Card %d: ", i);
        if (cardOnTable[i] <= 6) {
            printf("attack with point %d", cardOnTable[i]+1);
        } else {
            printf("shield with point %d", cardOnTable[i]-6);
        }
        printf("\n");
    }

    //int cardChosen = getCardFromKbd; //WHEN CONNECT TO KEYBOARD
    int cardChosen;
    printf("choose your card (0-2): "); // for debugging before connects to server
    scanf("%d", &cardChosen);
    int myCard = cardOnTable[cardChosen];

    // set valid of not picked cards to true
    for (int a = 0; a < 3; a++) {
        if (a != cardChosen) currPlayer->cards[cardOnTable[a]].valid = true;
    }

    return myCard;
}

// int getCardFromKbd() {
//     int cardIdx = 0;
//     bool cardChosen;

//     clock_t start = clock();
//     unsigned int kbd = 0x0;

//     while (clock() - start > TIME_LIMIT_CHOOSE_CARD) {
//         kbd = getKeycode();

//         if (kbd == KEY_ENTER1 || kbd == KEY_ENTER2 || kbd == KEY_SPACE) {
//             break;
//         } else if (kbd == KEY_RIGHT) {
//             cardIdx = (cardIdx + 1) % 3;
//             cardChosen = true;
//         } else if (kbd == KEY_LEFT) {
//             cardIdx = (cardIdx - 1) < 0 ? 4 : cardIdx - 1;
//             cardChosen = true;
//         }
//     }

//     /* Used when we decided to use random card when player did not choose card */
//     if (cardChosen) {
//         return cardIdx;
//     } else {
//         srand(time(NULL));
//         return rand()%3;
//     }
// }

#endif
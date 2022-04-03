/* HEADER FILES */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

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

/* FUNCTION DEFINITION */
struct player* playerInit(int playerID);
struct card* cardInit(int playerID);
void ultimateInit(struct player* players);
void calcHealth(int card_ID, struct player* player, int round_buff_id);
int chooseCard(struct player* currPlayer);


int main() {
    /* INITIALIZATION */
    // 0. initialize varibles
    bool isFirst; // tell who is chosing card first
    int myID;
    int oppoID;
    int round_buff;

    // 1. FROM SERVER: get order
    isFirst = true; // set for debugging; will get it from server
    myID = isFirst ? 0 : 1; // if I play first, my Id is 0
    oppoID = isFirst ? 1 : 0;

    // 2. initialize player array
    struct player* player_array[player_num];
    for (int i = 0; i < player_num; i++) {
        player_array[i] = playerInit(i);
    }

    // 3. initialize ultimate
    ultimateInit(player_array[myID]);

    /* GAME START */
    for (int round = 0; round < max_round; round++) {
        printf("\n\n round %d \n\n", round);
        round_buff = 0; // set for debugging; will get it from server
        struct player* currPlayer;

        if (isFirst) {
            int myCard = chooseCard(player_array[myID]);

            // TO SERVER: SEND Card chosen
            calcHealth(myCard, player_array[oppoID], round_buff);
            printf("\n your remaining health: %d \n", player_array[myID]->health);

            // FROM SERVER: get cardID that opponent chose
            int opponentCard = (rand() + (int) time(NULL)) % card_num;
            calcHealth(opponentCard, player_array[myID], round_buff);
            printf("\n opponent remaining health: %d \n", player_array[oppoID]->health);
        } else {
            // FROM SERVER: get cardID that opponent chose
            int opponentCard = (rand() + (int) time(NULL)) % card_num; // set for debugging; will get it from server
            calcHealth(opponentCard, player_array[myID], round_buff);
            printf("\n opponent remaining health: %d \n", player_array[oppoID]->health);

            // My turn to choose card
            int myCard = chooseCard(player_array[myID]);

            // TO SERVER: SEND Card chosen
            calcHealth(myCard, player_array[oppoID], round_buff);
            printf("\n your remaining health: %d \n", player_array[myID]->health);

        }

        // change shield
        player_array[myID] -> shield[player_array[myID] -> indexRemove] = 0; // Remove the old shield
        player_array[myID] -> indexAdd = (player_array[myID] -> indexAdd + 1) % 3;
        player_array[myID] -> indexRemove = (player_array[myID] -> indexRemove + 1) % 3;

        if (player_array[myID]->health < 0 || player_array[oppoID]->health < 0) {
            break;
        }
    }

    printf("\n\n");
    if (player_array[myID] > player_array[oppoID]) {
        printf("You won!\n");
    } else if (player_array[myID] = player_array[oppoID]) {
        printf("You lose =(");
    } else {
        printf("Draw");
    }


    return 0;
}


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

    player->ultimate = (rand() + (int) time(NULL)) % ult_num;

    if (player->ultimate == 2){
        player->health = 30;
    }

    printf("Player%d received ultimate %d!\n", player->player_ID, player->ultimate);

}

void calcHealth(int card_ID, struct player* player, int round_buff_id){
    // if player has round buff 2, attack point doubled
    int attack_card_multiplier = round_buff_id == 2 ? 2 : 1;
    int shield_multiplier = round_buff_id == 1 ? 2 : 1;

    // card from 0-6 is attack, 7-12 is defence
    if (card_ID <= 6){
        card_simple_attack((card_ID * attack_card_multiplier)+1, player);
    } else {
        card_simple_defence(card_ID * shield_multiplier, player);
    }
}

/* Functions for rounds */
int chooseCard(struct player* currPlayer) {
    // Draw 3 cards from deck
    int cardOnTable[3];
    int numDrew = 0;

    while (numDrew < 3) {
        // get random value between 0 and 12
        int randCard = (rand() + (int) time(NULL)) % card_num;
        // if current player has not used cards[randCard] before put it on table
        if (currPlayer->cards[randCard].valid == true) {
            cardOnTable[numDrew] = currPlayer->cards[randCard].card_ID;
            
            numDrew++; // increment number of cards on table
        }
    }

    printf("card on table for player %d\n", currPlayer->player_ID);
    for (int i = 0; i < 3; i++) {
        printf("Card %d: %d\n", i, cardOnTable[i]);
    }

    //int cardChosen = getCardFromKbd; //WHEN CONNECT TO KEYBOARD
    int cardChosen;
    printf("choose your card (0-2): "); // for debugging before connects to server
    scanf("%d", &cardChosen);
    int myCard = cardOnTable[cardChosen];

    // set valid of used card to false
    currPlayer->cards[myCard].valid = false;

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
//         return rand()%3;
//     }
// }
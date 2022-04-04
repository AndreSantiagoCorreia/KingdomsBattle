/* HEADER FILES */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

// personal header files
#include "game.h"


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
    // FROM SERVER: GET ULTIMATE NUMBER FOR OPPONENT
    // SEND TO VGA: ult info 

    /* GAME START */
    for (int round = 0; round < max_round; round++) {
        printf("\n\n round %d \n\n", round);
        // FROM SERVER: get round_buff
        // SEND TO VGA: buff number
        round_buff = 0; // set for debugging; will get it from server
        struct player* currPlayer;

        if (isFirst) {
            int myCard = chooseCard(player_array[myID]);

            // TO SERVER: SEND Card chosen
            cardFunction(player_array[oppoID], myCard, round_buff);
            printf("\n your remaining health: %d \n", player_array[myID]->health);

            // FROM SERVER: get cardID that opponent chose
            int opponentCard = (rand() + (int) time(NULL)) % card_num;
            // SEND TO VGA: enemy_card_visible (using random value between 0 to 1), enemy_card_used
            cardFunction(player_array[myID], opponentCard, round_buff);
            printf("\n opponent remaining health: %d \n", player_array[oppoID]->health);
        } else {
            // FROM SERVER: get cardID that opponent chose
            int opponentCard = (rand() + (int) time(NULL)) % card_num; // set for debugging; will get it from server
            // SEND TO VGA: enemy_card_visible (using random value between 0 to 1), enemy_card_used
            cardFunction(player_array[myID], opponentCard, round_buff);
            printf("\n opponent remaining health: %d \n", player_array[oppoID]->health);

            // My turn to choose card
            int myCard = chooseCard(player_array[myID]);

            // TO SERVER: SEND Card chosen
            cardFunction(player_array[oppoID], myCard, round_buff);
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
    } else if (player_array[myID] == player_array[oppoID]) {
        printf("You lose =(");
    } else {
        printf("Draw");
    }


    return 0;
}

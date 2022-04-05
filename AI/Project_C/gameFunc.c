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
    srand(time(NULL));
    // 0. initialize varibles
    bool isFirst; // tell who is chosing card first
    int myID;
    int oppoID;
    int round_buff;
    struct player* getEffect;

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
    ultimateInit(player_array[oppoID]); // just for debugging will get it from server
    // SEND TO VGA: ult info 

    /* GAME START */
    for (int round = 0; round < max_round; round++) {
        printf("\n\nround %d\n\n", round);
        // FROM SERVER: get round_buff
        // SEND TO VGA: buff number
        round_buff = rand() % 3; // set for debugging; will get it from server
        printf("round buff: %d\n", round_buff);
        struct player* currPlayer;

        if (isFirst) {
            // if round_buff == 0 && ultimate >= 3, ultimate 3 and 4 are active
            if (round_buff != 0 && player_array[myID]->ultimate >=3) {
                printf("Will you use ultimate this round? (1:yes, 0:no) ");
                scanf("%d", &player_array[myID]->ultUseThisRound); printf("\n");
                if (player_array[myID]->ultUseThisRound) {
                    // ultimate 4: disablt shield of opponent
                    if (player_array[myID]->ultimate == 4) {
                        player_array[oppoID]->shield[0] = 0;
                        player_array[oppoID]->shield[1] = 0;
                        player_array[oppoID]->shield[2] = 0;

                        player_array[myID]->ultimate = 0; // remove ultimate
                        player_array[myID]->ultUseThisRound = false; // ultimate is already used
                    }
                }
            }

            int myCard = chooseCard(player_array[myID]);

            // TO SERVER: SEND Card chosen
            getEffect = myCard <= 6 ? player_array[oppoID] : player_array[myID];
            cardFunction(getEffect, myCard, round_buff);

            // FROM SERVER: get cardID that opponent chose
            int opponentCard = rand() % card_num;
            printf("opponent's card: %d\n", opponentCard);
            // SEND TO VGA: enemy_card_visible (using random value between 0 to 1), enemy_card_used
            // if I'm using ultimate this round and ultimate is 3, opponent's card has same effect on opponent
            if (player_array[myID]->ultUseThisRound && player_array[myID]->ultimate == 3) {
                printf("ultimate 3 is enabled! Duplicate opponent's attack\n");
                cardFunction(player_array[oppoID], opponentCard, round_buff);
                cardFunction(player_array[myID], opponentCard, round_buff);

                player_array[myID]->ultimate = 0; // remove ultimate
                player_array[myID]->ultUseThisRound = false; // ultimate is already used
            } else {
                getEffect = opponentCard <= 6 ? player_array[myID] : player_array[oppoID];
                cardFunction(getEffect, opponentCard, round_buff);
            }

        } else {
            // FROM SERVER: get cardID that opponent chose
            int opponentCard = rand() % card_num; // set for debugging; will get it from server
            printf("opponent's card: %d\n", opponentCard);

            // if I'm using ultimate this round and ultimate is 3, opponent's card has same effect on opponent
            if (round_buff != 0 && player_array[myID]->ultUseThisRound && player_array[myID]->ultimate == 3) {
                printf("ultimate 3 is enabled! Duplicate opponent's attack\n");

                cardFunction(player_array[oppoID], opponentCard, round_buff);
                cardFunction(player_array[myID], opponentCard, round_buff);

                player_array[myID]->ultimate = 0; // remove ultimate
                player_array[myID]->ultUseThisRound = false; // ultimate is already used
            } else {
                getEffect = opponentCard <= 6 ? player_array[myID] : player_array[oppoID];
                cardFunction(getEffect, opponentCard, round_buff);
            }

            // My turn to choose card
            int myCard = chooseCard(player_array[myID]);

            // if round_buff == 0 || ultimate == 0, ultimate is disabled
            if (round_buff != 0 && player_array[myID]->ultimate >= 3) {
                printf("Will you use ultimate this round? (1:yes, 0:no) ");
                scanf("%d", &player_array[myID]->ultUseThisRound); printf("\n");
                if (player_array[myID]->ultUseThisRound) {
                    // ultimate 4: disablt shield of opponent
                    if (player_array[myID]->ultimate == 4) {
                        player_array[oppoID]->shield[0] = 0;
                        player_array[oppoID]->shield[1] = 0;
                        player_array[oppoID]->shield[2] = 0;

                        player_array[myID]->ultimate = 0; // remove ultimate
                        player_array[myID]->ultUseThisRound = false; // ultimate is already used
                    }
                }
            }

            // TO SERVER: SEND Card chosen
            getEffect = myCard <= 6 ? player_array[oppoID] : player_array[myID];
            cardFunction(getEffect, myCard, round_buff);
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

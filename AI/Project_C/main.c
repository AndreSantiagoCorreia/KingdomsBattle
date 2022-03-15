#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

#include<conio.h>

// other files
#include "Keyboard.h"

// need to be changed
#include "Data_type.h"
#include "Card_Function.h"
#include "ultimate_function.h"

// 13 cards
struct card* cardInitialization(int player);
void cardFunction(struct card _card, struct player* _player, int round_buff_id);
void ultimateInitialization(struct player* players);

// global variable
int playerNum;

int main(){

    printf("Player Number (2 - 5): \n");

    scanf("%d", &playerNum);

    if (playerNum > 5 || playerNum < 2){
        printf("Invalid input, value set to default: 2 \n");
        playerNum = player_num;
    }

    struct player* player_array = malloc(playerNum * sizeof(struct player));

    // initialize players
    for (int i = 0; i < playerNum; i++){
        player_array[i].cards = cardInitialization(i); //stores the pointers
        player_array[i].player_ID = i;
        player_array[i].health = 20;
        player_array[i].shield = 0;
        player_array[i].time_limit = 0; // 20 seconds time limit
        player_array[i].alive = true;

        //player_array[i].cardHolds = malloc(sizeof(struct card));
    }

    // initialize ultimates
    ultimateInitialization(player_array);

    int p_index = 0;

    int round = 0;
    bool roundbegin = true;
    int round_buff_id = -1; // not initialized

    ////////////////////////////////////////////////////
    // game play in round
    while(round < max_round){
        // do something with keyboard
        if (roundbegin) {
            roundbegin = false;
            /////////////////Check for round buff/////////////////
            round_buff_id = (rand() + (int) time(NULL)) % round_buff_num; // fake random..
            printf("----------Round Buff %d----------\n", round_buff_id);

            if (round_buff_id == 0){
                printf("All active ultimates are disabled in this round! \n");
            }
            else {
                if (round_buff_id == 3){
                    p_index = playerNum - 1;
                }
                /////////////////Begin of the round/////////////////
                /////////////////Check for ultimate 3 / 4(active)/////////////////
                for (int i = 0; i < playerNum; i++) {
                    if (player_array[i].ultimate == 3) {
                        printf("Player%d, press a number of the opponent to activate ultimate 3 in this round in 5 seconds \n",
                               player_array[i].player_ID);
                        clock_t thetime = clock();

                        int opid = -1;

                        while (opid == i || opid < 0 || opid >= playerNum) {

                            while (!kbhit()) {
                                if (clock() - thetime > 5000) {
                                    goto not_active;
                                }
                            }
                            scanf("%d", &opid);

                            if (opid == i || opid < 0 || opid >= playerNum)
                                printf("Another one! \n");

                        }
                        printf("Ultimate 3 is activated! \n");

                        player_array[i].ultimate = 300 * (opid + 5);

                        not_active:
                        continue;
                    } else if (player_array[i].ultimate == 4) {
                        printf("Player%d, press a number of the opponent to activate ultimate 4 in this round in 5 seconds \n",
                               player_array[i].player_ID);
                        clock_t thetime = clock();

                        int opid = -1;

                        while (opid == i || opid < 0 || opid >= playerNum) {

                            while (!kbhit()) {
                                if (clock() - thetime > 5000) {
                                    goto not_active2;
                                }
                            }
                            scanf("%d", &opid);

                            if (opid == i || opid < 0 || opid >= playerNum)
                                printf("Another one! \n");

                        }

                        player_array[opid].shield = 0;
                        player_array[i].ultimate = 0;
                        printf("Ultimate 4 is activated! \n");

                        not_active2:
                        continue;
                    }
                }
            }

        }

        struct player* current_player = &player_array[p_index];

        if (current_player -> alive) {
            printf("Round %d(player%d)\n\n", round, current_player->player_ID);

            current_player -> time_limit = clock(); // set current time to player

            // randomly draw 3 cards from the card deck...
            struct card *current_card_deck = malloc(card_deck_num * sizeof(struct card));

            // if the player has ultimate 3... then

            // probably need to update timer...
            while (clock() - current_player->time_limit <= 20 && current_player->alive) {

                // randomly choose 3 cards
                int index = 0;

                // currently, can draw out multiple same card !!!
                while (index < 3) {
                    int card_index = (rand() + (int) time(NULL)) % card_num; // 0 - 12, need a better random?
                    if (current_player->cards[card_index].valid == true) {
                        current_card_deck[index] = current_player->cards[card_index]; // append the card to the array, new copies
                        current_player->cards[card_index].valid = false;

                        printf("Card %d ---> Num%d\n", current_card_deck[index].card_ID, index + 1);

                        index++;
                    }
                }

                printf("\n");

                // reset the true / false
                index = 0;
                while (index < 3) {
                    current_player->cards[current_card_deck[index].card_ID].valid = true;
                    index++;
                }

                ////////////////////////////////////////////////////
                // user choose card
                //user_card_choice(current_player, current_card_deck);//

                int index_user = -1;
                int typeIn = 0;

                while (index_user > 2 || index_user < 0){

                    printf("Please choose your card (1 ~ 3): \n");

                    while(!kbhit()){
                        if (clock() - current_player->time_limit > TIME_UP){
                            printf("Time is up! \n");
                            goto out_of_time;
                        }
                    }

                    // currently, card information is not shown
                    scanf("%d", &typeIn);
                    index_user = typeIn - 1;
                }

                current_player -> cardHolds = current_card_deck[index_user];
                printf("Card %d being chosen\n", (current_player -> cardHolds).card_ID);

                // choose an opponent
                //user_object_choice(current_player, playerNum, player_array);//

                index_user = -1;

                while (index_user < 0 || index_user >= playerNum){
                    printf("Please choose an opponent (0 ~ %d): \n", playerNum - 1);

                    while(!kbhit()){
                        if (clock() - current_player->time_limit > TIME_UP){
                            printf("Time is up! \n");
                            goto out_of_time;
                        }
                    }

                    scanf("%d", &index_user);

                    if(!player_array[index_user].alive){
                        printf("Player%d is already eliminated...", index_user);
                        index_user = -1;
                        continue;
                    }
                }

                ////////////////////////////////////////////////////
                current_player -> objectID = index_user;

                // Object directed
                if (player_array[current_player -> objectID].ultimate > 100){
                    int opid = player_array[current_player -> objectID].ultimate / 300 - 5;
                    printf("Object directed from %d to %d! \n", current_player -> objectID, opid);
                    current_player -> objectID = opid;
                }

                printf("Player%d chooses the card ", current_player->player_ID);
                printf("%d, used on Player%d", (current_player->cardHolds).card_ID, current_player->objectID);
                printf("\n");

                cardFunction(current_player->cardHolds, &player_array[current_player->objectID], round_buff_id); //...
                sleep(1); // time to see status

                // disable using card id
                current_player->cards[(current_player->cardHolds).card_ID].valid = false;

                // Timer works well now
                out_of_time:

                free(current_card_deck);

                break;
            }

            printf("End Round (player%d)\n\n", current_player->player_ID);
        }

        // keep the loop
        if (round_buff_id == 3){
            p_index--;
            if (p_index < 0){
                p_index = 0;

                // all players used
                round++;
                roundbegin = true;
            }
        }
        else {
            p_index++;
            if (p_index >= playerNum){
                p_index = 0;

                // all players used
                round++;
                roundbegin = true;
            }
        }
    }

    return 0;
}

struct card* cardInitialization(int playerID){
    // array of cards
    struct card* card_array = malloc((card_num + 1) * sizeof(struct card));

    for (int i = 0; i < card_num; i++){
        card_array[i].card_ID = i; // index
        card_array[i].player_ID = playerID;
        card_array[i].valid = true; // set card to valid
    }

    return card_array;
}

// now we suppose card 1 - 6 is damage card, 7 - 13 is difference card
void cardFunction(struct card _card, struct player* player, int round_buff_id){
    int attack_card_multiplier = 1;

    if (round_buff_id == 2){
        attack_card_multiplier = 2;
    }

    if (_card.card_ID == 1){
        card_simple_attack(_card.card_ID * attack_card_multiplier, player);
    }
    else if (_card.card_ID == 2){
        card_simple_attack(_card.card_ID * attack_card_multiplier, player);
    }
    else if (_card.card_ID == 3){
        card_simple_attack(_card.card_ID * attack_card_multiplier, player);
    }
    else if (_card.card_ID == 4){
        card_simple_attack(_card.card_ID * attack_card_multiplier, player);
    }
    else if (_card.card_ID == 5){
        card_simple_attack(_card.card_ID * attack_card_multiplier, player);
    }
    else if (_card.card_ID == 6){
        card_simple_attack(_card.card_ID * attack_card_multiplier, player);
    }

        // defensive card here
    else if (_card.card_ID == 7){
        card_simple_defence(_card.card_ID, player);
    }
    else if (_card.card_ID == 8){
        card_simple_defence(_card.card_ID, player);
    }
    else if (_card.card_ID == 9){
        card_simple_defence(_card.card_ID, player);
    }
    else if (_card.card_ID == 10){
        card_simple_defence(_card.card_ID, player);
    }
    else if (_card.card_ID == 11){
        card_simple_defence(_card.card_ID, player);
    }
    else if (_card.card_ID == 12){
        card_simple_defence(_card.card_ID, player);
    }
    else if (_card.card_ID == 0){ // need to change
        card_simple_defence(_card.card_ID, player);
    }
}

void ultimateInitialization(struct player* players){
    // I don't know why this doesnt show... ***
    FILE* file = fopen("ult_description.txt", "r");
    int c;

    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
        fclose(file);
    }

    int ult;
    for (int i = 0; i < playerNum; i++){
        do {
            printf("\nPlayer%d, choose your ultimate:", players[i].player_ID);
            scanf("%d", &ult);
        } while(ult < 0 || ult > ult_num);

        players[i].ultimate = ult;

        if (players[i].ultimate == 2){
            players[i].health = 30;
        }

        printf("Player%d received ultimate %d!\n", players[i].player_ID, players[i].ultimate);
    }

}
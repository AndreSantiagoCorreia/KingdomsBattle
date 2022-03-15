#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

typedef uint32_t uint32;

// other files
#include "Keyboard.h"

// need to be changed
#include "Data_type.h"
#include "Card_Function.h"

// 13 cards
struct card* cardInitialization(int player);
void cardFunction(struct card _card, struct player _player);

// global variable
int playerNum;

void main(){

    printf("Player Number (2 - 5): \n");

    scanf("%d", playerNum);

    if (playerNum == NULL || playerNum > 5 || playerNum < 2){
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
    }

    int p_index = 0;

    int round = 0;

    // game play
    while(round < max_round){
        // do something with keyboard

        struct player current_player = player_array[p_index];

        current_player.time_limit = clock(); // set current time to player

        printf("Round %d(player%d)\n", round, current_player.player_ID);

        // probably need to update timer...
        while(clock() - current_player.time_limit >= 20 && current_player.alive){
            // the card being chosen
            struct card _card;

            // randomly draw 3 cards from the card deck...
            struct card* current_card_deck = malloc(card_deck_num * sizeof(struct card));

            // randomly choose 3 cards
            int index = 0;
            while (index < 3){
                int card_index = rand() % 13;
                current_card_deck[index] = current_player.cards[card_index]; // append the card to the array
                index++;
            }
            
            // user choose card
            user_card_choice(current_player, current_card_deck);

            // choose an opponent
            user_object_choice(current_player, playerNum);
            
            _card = current_player.cardHolds;

            printf("Player%d chooses the card%d\n", current_player.player_ID, _card.card_ID);

            cardFunction(_card, player_array[current_player.objectID]); //...

            // disable using card id
            current_player.cards[_card.card_ID].valid = false;
        }

        printf("End Round (player%d)\n", current_player.player_ID);

        // keep the loop
        p_index++;

        if (p_index >= playerNum){
            p_index = 0;

            // all players used
            round++;
        }
    }

    return;
}

struct card* cardInitialization(int playerID){
    // array of cards
    struct card* card_array = malloc(card_num * sizeof(struct card));

    for (int i = 1; i <= card_num; i++){
        card_array[i].card_ID = i;
        card_array[i].player_ID = playerID;
        card_array[i].valid = true; // set card to valid
    }

    return card_array;
}

// now we suppose card 1 - 6 is damage card, 7 - 13 is diffence card
void cardFunction(struct card _card, struct player _player){
    if (_card.card_ID == 1){
        card_simple_attack(_card.card_ID, _player);
    }
    else if (_card.card_ID == 2){
        card_simple_attack(_card.card_ID, _player);
    }
    else if (_card.card_ID == 3){
        card_simple_attack(_card.card_ID, _player);
    }
    else if (_card.card_ID == 4){
        card_simple_attack(_card.card_ID, _player);
    }
    else if (_card.card_ID == 5){
        card_simple_attack(_card.card_ID, _player);
    }
    else if (_card.card_ID == 6){
        card_simple_attack(_card.card_ID, _player);
    }

    // defensive card here
    else if (_card.card_ID == 7){
        card_simple_defence(_card.card_ID, _player);
    }
    else if (_card.card_ID == 8){
        card_simple_defence(_card.card_ID, _player);
    }
    else if (_card.card_ID == 9){
        card_simple_defence(_card.card_ID, _player);
    }
    else if (_card.card_ID == 10){
        card_simple_defence(_card.card_ID, _player);
    }
    else if (_card.card_ID == 11){
        card_simple_defence(_card.card_ID, _player);
    }
    else if (_card.card_ID == 12){
        card_simple_defence(_card.card_ID, _player);
    }
    else if (_card.card_ID == 13){
        card_simple_defence(_card.card_ID, _player);
    }
}
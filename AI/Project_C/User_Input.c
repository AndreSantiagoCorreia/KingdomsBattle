#include "Keyboard.h"

void user_card_choice(struct player* _player, struct card* current_card_deck){

    int index = -1;
    int typeIn = 0;

    while (index > 2 || index < 0){

        printf("Please choose your card (1 ~ 3): \n");

        // currently, card information is not shown
        scanf("%d", &typeIn);
        index = typeIn - 1;
    }

    _player -> cardHolds = current_card_deck[index];
    printf("Card %d being chosen\n", (_player -> cardHolds).card_ID);

    //memcpy(_player.cardHolds, &current_card_deck[index], sizeof(struct card));
}

void user_object_choice(struct player* _player, int playerNum, struct player* player_array){

    int index = -1;

    while (index < 0 || index >= playerNum){
        printf("Please choose an opponent (0 ~ %d): \n", playerNum - 1);

        scanf("%d", &index);

        if(!player_array[index].alive){
            printf("Player%d is already eliminated...", index);
            index = -1;
            continue;
        }
    }

    _player -> objectID = index;
}
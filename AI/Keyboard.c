#include "Keyboard.h"

void user_card_choice(struct player _player, struct card* current_card_deck){

    int index = -1;

    while (index > 3 || index < 0){ 

        printf("Please choose your card (1 ~ 3): \n");

        // currently card information is not shown 
        scanf("%d", index);

    }

    _player.cardHolds = current_card_deck[index];

    free(current_card_deck);
}

void user_object_choice(struct player _player, int playerNum){

    int index = -1;

    while (index < 0 || index > playerNum){
        printf("Please choose an opponent: \n");

        scanf("%d", index);
    }

    _player.objectID = index;
}
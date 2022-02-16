#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

typedef uint32_t uint32;

// need to be changed
#define player_num 2;
#define card_num 13;

// data types
struct card{
    int card_ID;    // 1 - 13
    int player_ID; // to be the same for 13 cards
}

struct player{
    // card* ?
    struct card cards[card_num]; // the card player holds
    int player_ID;
    int health; // initially 20
    struct card* cardHolds;
    clock_t time_limit; // need to work on it later
}

// 13 cards
struct card* cardInitialization(int player);
void cardFunction(struct card _card, struct player _player);

void main(){

    player* player_array = malloc(player_num * sizeof(struct player));

    for (int i = 0; i < player_num; i++){
        player_array[i].cards = cardInitialization(i); //stores the pointers
        player_array[i].player_ID = i;
        player_array[i].health = 20;
    }

    // game play
    while(1){
        // do something with keyboard

        cardFunction(card _card);
    }

    return;
}

struct card* cardInitialization(int playerID){
    // array of cards
    struct card* card_array = malloc(card_num * sizeof(struct card));

    for (int i = 1; i <= card_num; i++){
        card_array[i].card_ID = i;
        card_array[i].player_ID = playerID;
    }

    return card_array;
}

void cardFunction(struct card _card, struct player _player){
    if (_card.id == 1){

    }
    else if (_card.id == 2){

    }
    else if (_card.id == 3){

    }
    else if (_card.id == 4){

    }
    else if (_card.id == 5){

    }
    else if (_card.id == 6){

    }
    else if (_card.id == 7){

    }
    else if (_card.id == 8){

    }
    else if (_card.id == 9){

    }
    else if (_card.id == 10){

    }
    else if (_card.id == 11){

    }
    else if (_card.id == 12){

    }
    else if (_card.id == 13){

    }
}
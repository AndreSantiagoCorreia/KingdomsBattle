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

// 13 cards
struct card* cardInitialization(int player);
void cardFunction(struct card _card, struct player _player);

// card functions
void card_simple_attack(int damage, struct player _player);
void card_simple_defence(int shield, struct player _player);

void main(){

    struct player* player_array = malloc(player_num * sizeof(struct player));

    for (int i = 0; i < player_num; i++){
        player_array[i].cards = cardInitialization(i); //stores the pointers
        player_array[i].player_ID = i;
        player_array[i].health = 20;
        player_array[i].shield = 0;
        player_array[i].time_limit = 0; // 20 seconds time limit
        player_array[i].alive = true;
    }

    int p_index = 0;

    // game play
    while(1){
        // do something with keyboard

        struct player current_player = player_array[p_index];

        current_player.time_limit = clock(); // set current time to player

        printf("Round (player%d)\n", current_player.player_ID);

        // probably need to update timer...
        while(clock() - current_player.time_limit >= 20 && current_player.alive){
            struct card _card;

            // ... do something with keyboard and mouse...
            printf("Player%d chooses the card%d\n", current_player.player_ID, _card.card_ID);

            cardFunction(_card, struct player _object); //...

        }

        printf("End Round (player%d)\n", current_player.player_ID);

        // keep the loop
        p_index++;

        if (p_index >= player_num){
            p_index = 0;
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

void card_simple_attack(int damage, struct player _player){

    printf("The object of attack is Player%d\n", _player.player_ID);

    printf("Player%d receives %d damage\n", _player.player_ID, damage);

    _player.shield = _player.shield - damage;

    int remain_damage = 0 - _player.shield;

    if (remain_damage > 0){
        _player.health = _player.health - remain_damage;
    }

    printf("Player%d: Shield: %d \n Health: %d\n", _player.player_ID, _player.shield, _player.health);

    if (_player.health <= 0){
        printf("Player%d is eliminated!", _player.player_ID);

        _player.alive = false;
    }
}

void card_simple_defence(int shield, struct player _player){
    _player.shield = shield;
}
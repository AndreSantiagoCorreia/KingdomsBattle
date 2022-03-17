#include "Card_Function.h"
#include <time.h>

void card_simple_attack(int damage, struct player* _player){

    printf("The object of attack is Player%d\n", _player -> player_ID);

    printf("Player%d receives %d damage\n", _player -> player_ID, damage);

    // ultimate 1 is realized here
    if (_player -> ultimate == 1){
        printf("Player%d's ultimate 1 is activated, damage blocked. \n", _player -> player_ID);
        _player -> ultimate = 0;
        damage = 0;
    }

    _player -> shield = _player -> shield - damage;

    int remain_damage = 0 - _player -> shield;

    if (_player -> shield < 0){
        _player -> shield = 0;
    }

    if (remain_damage > 0){
        _player -> health = _player -> health - remain_damage;
    }

    printf("\n");
    printf("Player%d:\n    Shield: %d\n    Health: %d\n", _player -> player_ID, _player -> shield, _player -> health);
    printf("\n");

    if (_player -> health <= 0){
        printf("Player%d is eliminated!", _player -> player_ID);

        _player -> alive = false;
    }
}

void card_simple_defence(int shield, struct player* _player){
    _player -> shield = shield;

    printf("Player%d receives %d shield\n", _player -> player_ID, shield);

    printf("\n");
    printf("Player%d:\n    Shield: %d\n    Health: %d\n", _player -> player_ID, _player -> shield, _player -> health);
    printf("\n");
}
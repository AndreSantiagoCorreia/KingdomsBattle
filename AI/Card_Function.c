#include "Card_Function.h"

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
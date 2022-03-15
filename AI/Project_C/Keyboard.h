#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "Data_type.h"

void user_card_choice(struct player* _player, struct card* current_card_deck);
void user_object_choice(struct player* _player, int playerNum, struct player* player_array);
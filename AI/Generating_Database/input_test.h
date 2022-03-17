#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "Data_type.h"

void input_test_begin();
int input_test(int lower_bound, int upper_bound, int not_allowed, int player_id);
int input_test_ult(int lower_bound, int upper_bound, int not_allowed, int player_id);
void input_test_end();
#include "input_test.h"

void input_test_begin(){
    FILE *fptr = fopen("database.txt","w");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    fprintf(fptr, "%s", "Begin:\n");
}

void input_test_end(){
    FILE *fptr = fopen("database.txt","w");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    fprintf(fptr, "%s", "End\n\n\n");
}

int input_test(int lower_bound, int upper_bound, int not_allowed, int player_id){
    FILE *fptr = fopen("database.txt","w");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    // Player + player_id + : //
    char* playerString = "Player";
    char player_id_buffer[1];
    itoa(player_id, player_id_buffer, 10);
    strcat(playerString, player_id_buffer);
    strcat(playerString, ": ");
    fprintf(fptr, "%s", playerString);

    int divide = upper_bound - lower_bound - 1; // both not included

    int num = -1;

    do{
        num = (rand() + (int) time(NULL)) % divide;
        num = lower_bound + 1 + num;
    } while(num != not_allowed);

    // if player is eliminated.. // check not allowed list;

    fprintf(fptr, "%d", num);

    return num;
}

int input_test_ult(int lower_bound, int upper_bound, int not_allowed, int player_id){
    printf("u0");
    FILE *fptr = fopen("C:\\Users\\23612\\Documents\\CPEN_391\\Module_2\\l2c-39\\AI\\Generating_Database\\database.txt","w");

    printf("u2");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    // Player + player_id + : //
    char* playerString = "Player";
    char player_id_buffer[1];
    itoa(player_id, player_id_buffer, 10);
    strcat(playerString, player_id_buffer);
    strcat(playerString, ": ");
    fprintf(fptr, "%s", playerString);

    int divide = 10; // both not included

    int num = -1;

    do{
        num = (rand() + (int) time(NULL)) % divide;
    } while(num != not_allowed);

    if (num > 1){
        num = -1;
    }
    else{
        fprintf(fptr, "%d", num);
    }

    // if player is eliminated.. // check not allowed list;

    return num;


}
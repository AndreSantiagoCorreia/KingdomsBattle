#include "input_test_out.h"

#include "input_test.h"

void input_test_begin(int count){
    FILE *fptr = fopen("C:\\Users\\23612\\Documents\\CPEN_391\\Module_2\\l2c-39\\AI\\Generating_Database\\database.txt","a");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    fprintf(fptr, "%d\n", count);

    fprintf(fptr, "%s", "Begin:\n");

    fclose(fptr);
}

void input_test_end(int winner){
    FILE *fptr = fopen("C:\\Users\\23612\\Documents\\CPEN_391\\Module_2\\l2c-39\\AI\\Generating_Database\\database.txt","a");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    char playerString[10] = "Winner: ";
    char player_id_buffer[2];
    itoa(winner, player_id_buffer, 10);
    strcat(playerString, player_id_buffer);

    fprintf(fptr, "%s", playerString);
    fprintf(fptr, "%s", "\nEnd~~~\n\n\n");

    fclose(fptr);
}

int input_test(int lower_bound, int upper_bound, int not_allowed, int player_id){

    FILE *fptr = fopen("C:\\Users\\23612\\Documents\\CPEN_391\\Module_2\\l2c-39\\AI\\Generating_Database\\database.txt","a");

    if(fptr == NULL)
    {
        printf("Error!");
        printf("\nu200");
        exit(1);
    }

    // Player + player_id + : //

    char playerString[10] = "Player";
    char player_id_buffer[2];
    itoa(player_id, player_id_buffer, 10);
    strcat(playerString, player_id_buffer);
    strcat(playerString, ": ");
    fprintf(fptr, "%s", playerString);

    printf("%s", playerString);

    int divide = upper_bound - lower_bound - 1; // both not included

    int num = -1;

    do{
        num = (rand() + (int) time(NULL)) % divide;
        num = lower_bound + 1 + num;
        //printf("%d\n", num);
    } while(num == not_allowed);

    // if player is eliminated.. // check not allowed list;

    fprintf(fptr, "%d\n", num);

    fclose(fptr);

    return num;
}

int input_test_ult(int lower_bound, int upper_bound, int not_allowed, int player_id){

    FILE *fptr = fopen("C:\\Users\\23612\\Documents\\CPEN_391\\Module_2\\l2c-39\\AI\\Generating_Database\\database.txt","a");

    printf("u2");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    // Player + player_id + : //
    char playerString[13] = "UltPlayer";
    char player_id_buffer[2];
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
        fprintf(fptr, "%d\n", num);
    }

    // if player is eliminated.. // check not allowed list;
    fclose(fptr);

    return num;
}

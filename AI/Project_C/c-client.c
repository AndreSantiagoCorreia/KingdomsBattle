#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// personal header files
#include "game.h"
//#include "vga.h"

#define MAX 1024
#define PORT 53535
#define SA struct sockaddr

//Writes a message typed into the terminal to the server
void terminalToServer(int sockfd, char * buff, int n, int size );

//Writes a given string to server
void writeToServer(int sockfd, char * buff, int size );

//Gets Player Nickname and if he wants to play vs AI
void initializePlayer(int sockfd);

/* POINTERS FOR VGA OUTPUT */
// volatile int * CARD_SELECT_ptr;
// volatile int * MY_CARD_1_ptr;
// volatile int * MY_CARD_2_ptr;
// volatile int * MY_CARD_3_ptr;
// volatile int * MY_CARD_USED_ptr;
// volatile int * ENEMY_CARD_USED_ptr;
// volatile int * ENEMY_CARD_VISIBLE_ptr;
// volatile int * MY_HP_ptr;
// volatile int * MY_SHIELD_ptr;
// volatile int * TIME_ptr;
// volatile int * ROUND_ptr;
// volatile int * ENEMY_HP_ptr;
// volatile int * ENEMY_SHIELD_ptr;
// volatile int * BUFF_ptr;
// volatile int * ULT_INFO_ptr; 


void func(int sockfd)
{
    /* VARIABLES */
    char buff[MAX];
    char myRoundBuff[MAX];
    int n;

    bool isFirst; // tell who is chosing card first
    int myID;
    int oppoID;
    int round_buff;  
    struct player* getEffect; 

    initializePlayer(sockfd);

    /* INITIALIZATION */
    // 0. map memory

    // 1. FROM SERVER: get order
    isFirst = false; //defaults to false
    myID = isFirst ? 0 : 1; // if I play first, my Id is 0
    oppoID = isFirst ? 1 : 0;

    // 2. initialize player array
    struct player* player_array[player_num];
    for (int i = 0; i < player_num; i++) {
        player_array[i] = playerInit(i);
    }

    char oldRoundBuff;
    int ultInitialized = 0;

    //Start gaming (Gaming Loop)
    for (;;) {
        // Should contain the cards + ultimate played from opponent:
        //1st round server lets you know if you are the first one to play
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s\n", buff);
        
        //start contains the round buff for the very first round for some python reason
        char start = '\0';
        //only get the start char when string received from sever is: "You will start the round"
        if(strlen(buff) > 10) {
            start = buff[strlen(buff)-1];
        }

        if ((strncmp(&start, "0", 1)) != 0 && (strncmp(&start, "1", 1)) != 0 && (strncmp(&start, "2", 1)) != 0) {
            if(!ultInitialized){
                ultimateInit(player_array[myID]);
                ultInitialized = 1;
            }
            //should contain roundBuff number:
            bzero(myRoundBuff, sizeof(myRoundBuff));
            read(sockfd, myRoundBuff, sizeof(myRoundBuff));
            //Regular round calculations should go here:
            //buff contains opponent's card played and myRoundBuff contains round buff id******
            int round_buff = isFirst ? oldRoundBuff : *myRoundBuff-'0';
            if (!isFirst) printf("myRoundBuff: %d\n", round_buff);

            player_array[oppoID]->ultimate = atoi(&buff[0]);
            player_array[oppoID]->ultUseThisRound = atoi(&buff[2]);
            int opponentCard = atoi(&buff[4]);

            if (player_array[oppoID]->ultimate == 2 && player_array[oppoID]->ultUseThisRound) {
                player_array[oppoID]->health += 5;
                player_array[oppoID]->ultUseThisRound = false;
            }
        
            /* CHANGE VISIBILITY OF OPPONENT CARDS ON TABLE
            srand(time(NULL));
            int randOppCard = rand() % 3;
            if (randOppCard == 0) *ENEMY_CARD_VISIBLE_ptr = 0b110;
            else if (randOppCard == 1) *ENEMY_CARD_VISIBLE_ptr = 0b101;
            else *ENEMY_CARD_VISIBLE_ptr = 0b011;

            writeCard(ENEMY_CARD_USED_ptr, opponentCard, true);
             */

            if (player_array[myID]->ultUseThisRound && player_array[myID]->ultimate == 3) {
                printf("ultimate 3 is enabled! Duplicate opponent's attack\n");
                cardFunction(player_array[oppoID], opponentCard, round_buff);
                cardFunction(player_array[myID], opponentCard, round_buff);

                player_array[myID]->ultimate = 0; // remove ultimate
                player_array[myID]->ultUseThisRound = false; // ultimate is already used
            } else {
                getEffect = opponentCard <= 6 ? player_array[myID] : player_array[oppoID];
                cardFunction(getEffect, opponentCard, round_buff);
            }
            
            // *MY_HP_ptr = player_array[myID]->health;
            // *MY_SHIELD_ptr = player_array[myID]->shield[0] + player_array[myID]->shield[1] + player_array[myID]->shield[2];
            // *ENEMY_HP_ptr = player_array[oppoID]->health;
            // *ENEMY_SHIELD_ptr = player_array[oppoID]->shield[0] + player_array[oppoID]->shield[1] + player_array[oppoID]->shield[2];
                
            if (isFirst) {
                round_buff = *myRoundBuff-'0';
                oldRoundBuff = round_buff;

                player_array[myID] -> shield[player_array[myID] -> indexRemove] = 0; // Remove the old shield
                player_array[myID] -> indexAdd = (player_array[myID] -> indexAdd + 1) % 3;
                player_array[myID] -> indexRemove = (player_array[myID] -> indexRemove + 1) % 3;
                player_array[oppoID] -> shield[player_array[oppoID] -> indexRemove] = 0; // Remove the old shield
                player_array[oppoID] -> indexAdd = (player_array[oppoID] -> indexAdd + 1) % 3;
                player_array[oppoID] -> indexRemove = (player_array[oppoID] -> indexRemove + 1) % 3;

                printf("player%d shield [%d %d %d]\n", myID, player_array[myID]->shield[0], player_array[myID]->shield[1], player_array[myID]->shield[2]);
                printf("player%d shield [%d %d %d]\n", oppoID, player_array[oppoID]->shield[0], player_array[oppoID]->shield[1], player_array[oppoID]->shield[2]);
            }

            if (player_array[myID]->health <= 0 || player_array[oppoID]->health <= 0) {
                //void writeToServer(int sockfd, char * buff, int size );
                char gameEnded[MAX] = "gameEnded";
                writeToServer(sockfd, gameEnded, sizeof(gameEnded));
            }

            printf("myRoundBuff : %s\n", myRoundBuff);

            //int myCard = chooseCard(player_array[myID], MY_CARD_1_ptr, MY_CARD_2_ptr, MY_CARD_3_ptr);
            // if round_buff == 0 && ultimate <= 2, user do not have choice about ultimate
            if (round_buff != 0 && player_array[myID]->ultimate >= 3) {
                printf("Will you use ultimate this round? (1:yes, 0:no) ");
                scanf("%d", &player_array[myID]->ultUseThisRound); printf("\n");
                if (player_array[myID]->ultUseThisRound) {
                    // ultimate 4: disablt shield of opponent
                    if (player_array[myID]->ultimate == 4) {
                        player_array[oppoID]->shield[0] = 0;
                        player_array[oppoID]->shield[1] = 0;
                        player_array[oppoID]->shield[2] = 0;

                        player_array[myID]->ultimate = 0; // remove ultimate
                        player_array[myID]->ultUseThisRound = false; // ultimate is already used
                    }
                }
            }

            int myCard = chooseCard(player_array[myID]);

            // if card is for attack opponent get effect, if card is for shield I get effect
            if (player_array[oppoID]->ultUseThisRound && player_array[oppoID]->ultimate == 3) {
                printf("ultimate 3 is enabled! Duplicate opponent's attack\n");
                cardFunction(player_array[oppoID], myCard, round_buff);
                cardFunction(player_array[myID], myCard, round_buff);

                player_array[oppoID]->ultimate = 0; // remove ultimate
                player_array[oppoID]->ultUseThisRound = false; // ultimate is already used
            } else {
                getEffect = myCard <= 6 ? player_array[oppoID] : player_array[myID];
                cardFunction(getEffect, myCard, round_buff);
            }
            // *BUFF_ptr = round_buff;
            // *MY_HP_ptr = player_array[myID]->health;
            // *MY_SHIELD_ptr = player_array[myID]->shield[0] + player_array[myID]->shield[1] + player_array[myID]->shield[2];
            // *ENEMY_HP_ptr = player_array[oppoID]->health;
            // *ENEMY_SHIELD_ptr = player_array[oppoID]->shield[0] + player_array[oppoID]->shield[1] + player_array[oppoID]->shield[2];            
            printf("\n your remaining health: %d \n", player_array[myID]->health);

            //writing our card of choice to the server:
            char myCardString[MAX];
            sprintf(myCardString, "%d %d %d", player_array[myID]->ultimate, player_array[myID]->ultUseThisRound, myCard);
            writeToServer(sockfd, myCardString, sizeof(myCardString));

            if (player_array[myID]->health <= 0 || player_array[oppoID]->health <= 0) {
                //void writeToServer(int sockfd, char * buff, int size );
                char gameEnded[MAX] = "gameEnded";
                writeToServer(sockfd, gameEnded, sizeof(gameEnded));
            }
        
            // remove old shield
            if (!isFirst) {
                player_array[myID] -> shield[player_array[myID] -> indexRemove] = 0; // Remove the old shield
                player_array[myID] -> indexAdd = (player_array[myID] -> indexAdd + 1) % 3;
                player_array[myID] -> indexRemove = (player_array[myID] -> indexRemove + 1) % 3;
                player_array[oppoID] -> shield[player_array[oppoID] -> indexRemove] = 0; // Remove the old shield
                player_array[oppoID] -> indexAdd = (player_array[oppoID] -> indexAdd + 1) % 3;
                player_array[oppoID] -> indexRemove = (player_array[oppoID] -> indexRemove + 1) % 3;

                
                printf("player%d shield [%d %d %d]\n", myID, player_array[myID]->shield[0], player_array[myID]->shield[1], player_array[myID]->shield[2]);
                printf("player%d shield [%d %d %d]\n", oppoID, player_array[oppoID]->shield[0], player_array[oppoID]->shield[1], player_array[oppoID]->shield[2]);
            }

            // reset enemy card visibility on VGA
            // *ENEMY_CARD_VISIBLE = 0b111;

        } else {
            //Means you are the first one to play!
            printf("\nmyRoundBuff : %c\n", start);

            printf("\n\nbuff: %s\n\n", buff);

            //First round should go here:
            //buff contains garbage and start contains the round buff id******
            int round_buff = start-'0';
            oldRoundBuff = round_buff;
            // *BUFF_ptr = round_buff;
            
            isFirst = true;
            myID = isFirst ? 0 : 1; // if I play first, my Id is 0
            oppoID = isFirst ? 1 : 0;

            // 3. initialize ultimate
            ultimateInit(player_array[myID]);
            ultInitialized = 1;

            // if round_buff == 0 || ultimate <= 2 user do not have choice about ultimate
            if (round_buff != 0 && player_array[myID]->ultimate >= 3) {
                printf("Will you use ultimate this round? (1:yes, 0:no) ");
                scanf("%d", &player_array[myID]->ultUseThisRound); printf("\n");
                if (player_array[myID]->ultUseThisRound) {
                    // ultimate 4: disablt shield of opponent
                    if (player_array[myID]->ultimate == 4) {
                        player_array[oppoID]->shield[0] = 0;
                        player_array[oppoID]->shield[1] = 0;
                        player_array[oppoID]->shield[2] = 0;

                        player_array[myID]->ultimate = 0; // remove ultimate
                        player_array[myID]->ultUseThisRound = false; // ultimate is already used
                    }
                }
            }

            int myCard = chooseCard(player_array[myID]);
            // if card is for attack opponent get effect, if card is for shield I get effect
            getEffect = myCard <= 6 ? player_array[oppoID] : player_array[myID];
            cardFunction(getEffect, myCard, round_buff);
            printf("\n your remaining health: %d \n", player_array[myID]->health);

            if (player_array[myID]->health <= 0 || player_array[oppoID]->health <= 0) {
                //void writeToServer(int sockfd, char * buff, int size );
                char gameEnded[MAX] = "gameEnded";
                writeToServer(sockfd, gameEnded, sizeof(gameEnded));
            }

            //writing our card of choice to the server:
            char myCardString[MAX];
            sprintf(myCardString, "%d %d %d", player_array[myID]->ultimate, player_array[myID]->ultUseThisRound, myCard);
            player_array[myID]->ultUseThisRound = false;
            writeToServer(sockfd, myCardString, sizeof(myCardString));
        }
        
        //writing our card of choice to the server:
        //char myCardString[MAX];
        //sprintf(myCardString, "%d", myCard);
        //terminalToServer(sockfd, buff, n, sizeof(buff));
    }
}
   
int main()
{
    /* map memory */
    // int fd = -1;               // used to open /dev/mem for access to physical addresses
    // void *LW_virtual;          // used to map physical addresses for the light-weight bridge

    // // Create virtual memory access to the FPGA light-weight bridge
    // if ((fd = open_physical (fd)) == -1)
    //     return (-1);
    // if ((LW_virtual = map_physical (fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN)) == NULL)
    //     return (-1);
    
    // CARD_SELECT_ptr = (unsigned int *) (LW_virtual + 0x00000030);
    // MY_CARD_1_ptr = (unsigned int *) (LW_virtual + 0x00000040);
    // MY_CARD_2_ptr = (unsigned int *) (LW_virtual + 0x00000050);
    // MY_CARD_3_ptr = (unsigned int *) (LW_virtual + 0x00000060);
    // MY_CARD_USED_ptr = (unsigned int *) (LW_virtual + 0x00000070);
    // ENEMY_CARD_USED_ptr = (unsigned int *) (LW_virtual + 0x00000080);
    // ENEMY_CARD_VISIBLE_ptr = (unsigned int *) (LW_virtual + 0x00000090);
    // MY_HP_ptr = (unsigned int *) (LW_virtual + 0x000000a0);
    // MY_SHIELD_ptr = (unsigned int *) (LW_virtual + 0x000000b0);
    // TIME_ptr = (unsigned int *) (LW_virtual + 0x000000c0);
    // ROUND_ptr = (unsigned int *) (LW_virtual + 0x000000d0);
    // ENEMY_HP_ptr = (unsigned int *) (LW_virtual + 0x000000e0);
    // ENEMY_SHIELD_ptr = (unsigned int *) (LW_virtual + 0x000000f0);
    // BUFF_ptr = (unsigned int *) (LW_virtual + 0x00000100);
    // ULT_INFO_ptr = (unsigned int *) (LW_virtual + 0x00000110);

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("%d\n", PORT);
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server...\n");
   
    // function for chat
    func(sockfd);
   
    // close the socket
    close(sockfd);
}

//write a given string to server
void writeToServer(int sockfd, char * buff, int size ){
    //writing our card of choice to the server:
    write(sockfd, buff, size);
}

//writes a message typed into the terminal to the server
void terminalToServer(int sockfd, char * buff, int n, int size ){
     //writing our card of choice to the server:
    bzero(buff, size);
    printf("Play a card (1-4) : ");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
        ;
    write(sockfd, buff, size);
    bzero(buff, size);
}

//Gets Player Nickname and if he wants to play vs AI
void initializePlayer(int sockfd) {
    char buff[MAX];
    char myRoundBuff[MAX];
    int n;
    //Single Player
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("From Server : %s\n", buff);
    bzero(buff, sizeof(buff));
    printf("Would you like to play Singleplayer mode (Y/N): ");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
        ;
    write(sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));
    //Nickname
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("From Server : %s\n", buff);
    bzero(buff, sizeof(buff));
    printf("Choose your Nickname: ");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
        ;
    write(sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));

}
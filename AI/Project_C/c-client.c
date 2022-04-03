#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// personal header files
#include "Data_type.h"
#include "Card_Function.h"
#include "game.h"
//#include "Keyboard.h"

#define MAX 1024
#define PORT 23535
#define SA struct sockaddr

//Writes a message typed into the terminal to the server
void terminalToServer(int sockfd, char * buff, int n, int size );

//Writes a given string to server
void writeToServer(int sockfd, char * buff, int size );

//Gets Player Nickname and if he wants to play vs AI
void initializePlayer(int sockfd);


void func(int sockfd)
{
    char buff[MAX];
    char myRoundBuff[MAX];
    int n;

    initializePlayer(sockfd);

    /* INITIALIZATION */
    // 0. initialize varibles
    bool isFirst; // tell who is chosing card first
    int myID;
    int oppoID;
    int round_buff;

    // 1. FROM SERVER: get order
    isFirst = false; //defaults to false
    myID = isFirst ? 0 : 1; // if I play first, my Id is 0
    oppoID = isFirst ? 1 : 0;

    // 2. initialize player array
    struct player* player_array[player_num];
    for (int i = 0; i < player_num; i++) {
        player_array[i] = playerInit(i);
    }

    //Start gaming (Gaming Loop)
    for (;;) {
        // Should contain the cards + ultimate played from opponent:
        //1st round server lets you know if you are the first one to play
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        
        //start contains the round buff for the very first round for some python reason
        char start = '\0';
        //only get the start char when string received from sever is: "You will start the round"
        if(strlen(buff) > 10) {
            start = buff[strlen(buff)-1];
        }
        if ((strncmp(&start, "0", 1)) != 0 && (strncmp(&start, "1", 1)) != 0 && (strncmp(&start, "2", 1)) != 0) {
            //should contain roundBuff number:
            bzero(myRoundBuff, sizeof(myRoundBuff));
            read(sockfd, myRoundBuff, sizeof(myRoundBuff));
            printf("myRoundBuff : %s\n", myRoundBuff);
            //Regular round calculations should go here:
            //buff contains opponent's card played and myRoundBuff contains round buff id******
            int round_buff = *myRoundBuff-'0';

            int opponentCard = atoi(buff);
            printf("OPPS CARD: %d", opponentCard);
            calcHealth(opponentCard, player_array[myID], round_buff);

        } else {
            //Means you are the first one to play!
            printf("\nmyRoundBuff : %c\n", start);
            //First round should go here:
            //buff contains garbage and start contains the round buff id******
            int round_buff = start-'0';
            
            isFirst = true;
            myID = isFirst ? 0 : 1; // if I play first, my Id is 0
            oppoID = isFirst ? 1 : 0;

            int myCard = chooseCard(player_array[myID]);
            // TO SERVER: SEND Card chosen
            calcHealth(myCard, player_array[oppoID], round_buff);
            printf("\n your remaining health: %d \n", player_array[myID]->health);

            //writing our card of choice to the server:
            char myCardString[MAX];
            sprintf(myCardString, "%d", myCard);
            writeToServer(sockfd, myCardString, sizeof(myCardString));
        }
        
        //writing our card of choice to the server:
        //char myCardString[MAX];
        //sprintf(myCardString, "%d", myCard);
        terminalToServer(sockfd, buff, n, sizeof(buff));
    }
}
   
int main()
{
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
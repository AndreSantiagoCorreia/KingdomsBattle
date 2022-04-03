#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 1024
#define PORT 23535
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    char myRoundBuff[MAX];
    int n;

    //Single Player
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("From Server : %s", buff);
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
    printf("From Server : %s", buff);
    bzero(buff, sizeof(buff));
    printf("Choose your Nickname: ");
    n = 0;
    while ((buff[n++] = getchar()) != '\n')
        ;
    write(sockfd, buff, sizeof(buff));
    bzero(buff, sizeof(buff));

    //Start gaming
    for (;;) {
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From Server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
         char start = buff[strlen(buff)-1];
        // printf("START IS: %c", start);
        // while ((strncmp(&start, "g", 1)) != 0) {
        //     //busy waiting for my turn to play
        //     bzero(buff, sizeof(buff));
        //     read(sockfd, buff, sizeof(buff));
        //     printf("%s", buff);
        //     char start = buff[strlen(buff)-1];
        // }
        //start contains the round buff for the very first round for some python reason
        if ((strncmp(&start, "0", 1)) != 0 && (strncmp(&start, "1", 1)) != 0 && (strncmp(&start, "2", 1)) != 0 && (strncmp(&start, ".", 1)) != 0) {
            bzero(myRoundBuff, sizeof(myRoundBuff));
            read(sockfd, myRoundBuff, sizeof(myRoundBuff));
            printf("myRoundBuff : %s\n", myRoundBuff);
        } else {
            printf("myRoundBuff : %c\n", start);
        }

        if((strncmp(&start, ".", 1)) != 0) {
            bzero(buff, sizeof(buff));
            printf("Play a card (1-4) : ");
            n = 0;
            while ((buff[n++] = getchar()) != '\n')
                ;
            write(sockfd, buff, sizeof(buff));
            bzero(buff, sizeof(buff));
        }
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
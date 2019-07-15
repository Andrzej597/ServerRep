#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>

#define PORT 8080
//#define bzero(b,len) (memset)

//#pragma comment (lib, "ws2_32.lib")

using namespace std;

void error (char *msg){
    perror(msg);
    cout << "err";
    exit(1);
}

int main (int argc, char * argv[]){
    int sockfd;
    int newsockfd;
    int portnum;
    int n;
    socklen_t clientlen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    if(argc<2)
    {
        cout << "ERROR\n";
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        error("ERROR");
    }
    else{
       // printf("success");
        cout << "success";
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portnum = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portnum);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
                  error("ERROR");
    }
    listen(sockfd,5);
    clientlen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clientlen);
    if(newsockfd<0){
        error("ERROR");
    }
    printf ("meassage is: %s\n", buffer);
    cout << "message is:%s\n", buffer;
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0){
        error("ERROR");
    }
    printf("Message: %s\n",buffer);
    cout << "message:%s\n", buffer;
    n = write(newsockfd,"message",18);
    if (n < 0) error("ERROR");
    close (newsockfd);
    close(sockfd);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

int func1(int sockfd) 
{ 
    char            host_name[80];
    struct hostent *host_entry;
    int             ndx;
                 
    if ( 0 != gethostname( host_name, sizeof( host_name)))
    {
        printf("gethostname() 실행 실패/n");
        exit( 1);
    }                 
    
    printf("Get from Server - Host Name : %s\n", host_name);
    write(sockfd, host_name, sizeof(host_name)); 
    printf("Get from Server - PORT : 8080\n");

    host_entry = gethostbyname( host_name);

    if ( !host_entry)
    {
        printf("gethostbyname() 실행 실패/n");
        exit( 1);
    }
    for ( ndx = 0; NULL != host_entry->h_addr_list[ndx]; ndx++)
        printf("Get from Server - IP-Address : %s\n", inet_ntoa( *(struct in_addr*)host_entry->h_addr_list[ndx]));
    
    
    return 0;
}

/*
void func2(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("Enter the string : "); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
*/
int main() 
{ 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and varification 
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
    servaddr.sin_port = htons(PORT); 
  
    // connect the client socket to server socket 
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0) { 
        printf("bind : connection refuse\n"); 
        exit(0); 
    } 
    else
        printf("connected to the server..\n"); 
  
    // function for chat 
    func1(sockfd); 
  
    // close the socket 
    close(sockfd); 
} 
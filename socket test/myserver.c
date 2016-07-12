#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE (4096)
#define PORT (6666)
int main(int argc, char** argv)
{
    int listenfd,connectfd;
    struct sockaddr_in serverAddr;
    char buffer[MAXLINE];
    int n;
    // create listen socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        printf("create socket error: %s(errno : %d)\n", strerror(errno), errno);
        return -1;
    }
    
    // bind socket and port
    memset(&serverAddr, 0 , sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);
    if(bind(listenfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }
    
    // listen
    if(listen(listenfd, 10) == -1)
    {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }
    
    // wait for client's request
    printf("======waiting for client's request=======\n");
    connectfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    if(connectfd == -1)
    {
        printf("accept socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }
    while(1)
    {
        n = recv(connectfd, buffer, MAXLINE, 0);
        if (n == 0) {
            printf("client closed connection\n");
            break;
        }
        buffer[n] = '\0';
        printf("receive msg from client: %s\n", buffer);
    }
    close(connectfd);;
    close(listenfd);
    return 0;;
}

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define N 1024


int main(int argc, char **argv)
{
struct sockaddr_in server_addr, client_addr;
int sfd,count, slen=sizeof(server_addr);
char recv_buff[N],send_buff[N]="this is an UDP client, send me response";

sfd=socket(AF_INET,SOCK_DGRAM,0);
memset(&server_addr, '0', sizeof(server_addr));
memset(&client_addr, '0', sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000); 
    server_addr.sin_addr.s_addr = inet_addr("192.168.25.119");//htonl(INADDR_ANY);
    
count=sendto(sfd, send_buff, 1024, 0,(struct sockaddr*)&server_addr, slen);
count=recvfrom(sfd, recv_buff, 1024, 0, (struct sockaddr*)NULL, NULL);
printf("%s\n",recv_buff);
}


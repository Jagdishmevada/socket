#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#define N 256
#define M 256
#define L 5
#define IP "127.0.0.1"
int main(int argc, char **argv)
{
int count,slen;
char recv_buff[N],send_buff[N]="server:Roger, your IP is ",ipa[N], msg[N];
char *buf=(char *)malloc(sizeof(char)*M);//
int len,fd1,fd2;//


struct sockaddr_in server_addr, client_addr;
memset(&server_addr, '0', sizeof(server_addr));
slen=sizeof(server_addr);

int sfd,commsfd,j=0;

sfd=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);// inet_addr(IP);
    server_addr.sin_port = htons(atoi(argv[2])); 

bind(sfd, (struct sockaddr*) &server_addr, sizeof(server_addr)); 
listen(sfd,L); // Non-BLocking.. 
while(1){
       commsfd=accept(sfd,(struct sockaddr*) &client_addr,&slen);// BLocking.. 
        j++;
	if(fork()==0)//child process
		{
                		
		close(sfd);
		count=recv(commsfd, recv_buff, N,0);
		printf("client %d: %s\n",j,recv_buff);
		/*strcpy(msg,"1");
		count=send(commsfd, send_buff, strlen(msg),0);
		if (strcmp(send_buff,msg)!=0){
		strcpy(msg,"Denied");
		count=send(commsfd, send_buff, strlen(msg),0);
		exit(0);
		}
		else	{*/
			fd1=open(argv[1], O_RDONLY);//
			len=read(fd1,buf,M);
				while(len>0)
				{
				count=write(commsfd, buf, len);				
				len=read(fd1,buf,M);
			//	printf("%d len",len);				
				}
			printf("session over for client %d\n",j);
			exit(0);
			//}
	        } //child
	close(commsfd);
	}//while
close(fd1);
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<arpa/inet.h>
#define PORT 6500

void error(char *);

int main(int argc, char *argv[])
{
int sockfd, length, n;
struct sockaddr_in server, from;
struct hostent *hp;
char buffer[1000];

if (argc != 3)
{
printf("Usage: server port\n");
exit(1);
}

sockfd= socket(AF_INET, SOCK_DGRAM, 0);
hp=gethostbyname(argv[1]);
 server.sin_family=AF_INET;

  bcopy((char *)hp ->h_addr, 
         (char *)&server.sin_addr,
         hp ->h_length);

server.sin_port = htons(PORT);
length=sizeof(struct sockaddr_in);

FILE *f;
sendto(sockfd,argv[2],sizeof(argv[2]),0,&server,length);
//write(sockfd,argv[2],sizeof(argv[2]));
f=fopen(argv[2],"r");
fread(buffer,1000,1,f);
sendto(sockfd,buffer,1000,0,&server,length);
bzero(buffer,1000);
//read(sockfd,buffer,1000);
recvfrom(sockfd,buffer,1000,0,&from, &length);
printf("%s\n",buffer);
close(sockfd);
return 0;
}

void error(char *msg)
{
perror(msg);
exit(0);
}


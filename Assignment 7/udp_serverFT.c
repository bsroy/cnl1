/* Creates a datagram server. The port number is passed as an argument. This server runs forever */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#define PORT 6500

void error(char *msg)
{
perror(msg);
exit(0);
}

int main(int argc, char *argv[])
{
int sockfd, length, fromlen, n;
struct sockaddr_in server;
struct sockaddr_in from;
char buffer[1000],fname[25];

sockfd=socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0)
{
error("Opening socket");
}
length = sizeof(server);
bzero(&server,length);
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(PORT);
if (bind(sockfd,(struct sockaddr *)&server,length)<0)
{
error("binding");
}
fromlen = sizeof(struct sockaddr_in);

 
FILE *fp;
//read(newsockfd,fname,sizeof(fname));
 recvfrom(sockfd,fname,sizeof(fname),0,(struct sockaddr *)&from,&fromlen);
fp=fopen(fname,"w");
//read(newsockfd,buffer,1000);
recvfrom(sockfd,buffer,1000,0,(struct sockaddr *)&from,&fromlen);
fwrite(buffer,strlen(buffer),1,fp);
//write(newsockfd,"The file has been sent successfully",30);
sendto(sockfd,"The file has been sent successfully",30,
0,(struct sockaddr *)&from,fromlen);
printf("The contents of the file are  : \n\n");
printf("%s\n",buffer);
close(fp);
//close(newsockfd);
close(sockfd);
return 0; 
}

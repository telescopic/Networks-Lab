#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
int main(int argc,char **argv)
{
int len;
int sockfd,n;
struct sockaddr_in servaddr,cliaddr;
char str[1000],inp[100];
char buff[1024];
char dest[100];
strcat(buff,"");
FILE *fd;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
perror("cannot create socket(s)");
bzero(&servaddr,sizeof(servaddr));

servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr(argv[1]);
servaddr.sin_port=htons(7111);
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
//Accepting the filename
printf("Enter the filepath and destination path (space separated):\n");
//printf("%s",buff);
scanf("%s %s",buff,dest);
printf("%s\n",dest);
//Sending filename to server
n=write(sockfd,buff,sizeof(buff));
n=read(sockfd,buff,sizeof(buff));
printf("File received and written to directory: %s \n",dest);
fd=fopen(dest,"w");
if(fd==NULL) {printf("Bad path\n"); return 0;}
fputs(buff,fd);
close(sockfd);
return 0;
}

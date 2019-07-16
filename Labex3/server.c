#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
int main(int argc,char **argv)
{
int len;
int sockfd,newfd,n;
FILE *fd;
struct sockaddr_in servaddr,cliaddr;
char buff[1024];
char str[1000];
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
perror("cannot create socket");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=INADDR_ANY;
servaddr.sin_port=htons(7111);	
if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
perror("Bind error");
listen(sockfd,2);
len=sizeof(cliaddr);
newfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
//Receiving the filename
n=read(newfd,buff,sizeof(buff));
printf("File to be read:%s\n",buff);
//filename stored in buff
fd=fopen(buff,"r"); //opening the file
if(fd==NULL){printf("Error\n"); return 0;}
printf("\nFile %s sent to client\n",buff);	
fread(buff,sizeof(buff),1,fd); //read contents of the file
printf("File content: \n %s \n",buff);
//printf("%s",buff);
write(newfd,buff,sizeof(buff));
printf("File sent to client\n");
close(sockfd);
close(newfd);
return 0;
}

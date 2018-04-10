#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define PORT 1250
#define MAX_DATA 1024
int main()
{

FILE *fp;
int server_fd,new_socket;
char f[80],s[80];
char data[MAX_DATA];

struct sockaddr_in address,clientaddr;
int addrlen = sizeof(address);
int clielen = sizeof(clientaddr);

if((server_fd = socket(AF_INET,SOCK_STREAM,0))==0){
perror("socket failed");
exit(EXIT_FAILURE);
}

bzero(&address,addrlen);

address.sin_family = AF_INET;
address.sin_port = htons(PORT);


if(bind(server_fd,(struct sockaddr*)&address,sizeof(address))<0)
{
perror("bind failed");
exit(EXIT_FAILURE);
}

if(listen(server_fd,1)<0)
{
perror("LISTENERROR");
exit(EXIT_FAILURE);
}

if((new_socket = accept(server_fd,(struct sockaddr*)&clientaddr,(socklen_t*)&clielen))<0)
{
perror("error");
exit(EXIT_FAILURE);
}

int data_len=1;
while(data_len)
{
	data_len=recv(new_socket,data,MAX_DATA,0);
  if(data_len){
    send(new_socket,data,data_len,0);
    printf("sent message:%s",data);
  }
}

/*read(new_socket,f,80);
fp = fopen(f,"r");
printf("filename %s\n",f);
while(fgets(s,80,fp)!=NULL)
{
write(new_socket,s,sizeof(s));
}
*/
close(new_socket);
fclose(fp);
}


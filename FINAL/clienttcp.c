#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#define PORT 1250
#define BUFFER 1024
int main(int argc,char **argv)
{
int client_fd;
struct sockaddr_in address;
int addrlen = sizeof(address);
char filename[80],recv[80];
char input[BUFFER];
char output[BUFFER];
int len;
if((client_fd = socket(AF_INET,SOCK_STREAM,0))==0)
{
perror("SOCKET FAILURE");
exit(EXIT_FAILURE);
}

bzero(&address,addrlen);

address.sin_family = AF_INET;
address.sin_port = htons(PORT);

inet_pton(AF_INET,argv[1],&address.sin_addr);

connect(client_fd,(struct sockaddr*)&address,addrlen);


while(1)
{
	fgets(input,BUFFER,stdin);
	send(client_fd,input,strlen(input),0);
	len = recv(client_fd,output,strlen(output),0);
	output[len]='\0';
	printf("%s\n",output);
	
}


/*printf("enter filename");
scanf("%s",filename);
write(client_fd,filename,80);
while((read(client_fd,recv,80)!=0))
	printf("%s",recv);
close(client_fd);
*/
}


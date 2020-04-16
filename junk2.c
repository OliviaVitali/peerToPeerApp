//attempt 2 at program
//Olivia Vitali

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h> 
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <math.h>

void error(char *msg){
	perror(msg);
	exit(1);
}
int getPortNo();
int getPeerNo(int portno);
int firstOnline();
void dostuff(int);//puts self online
int connectServer(int, int);//connects to known port

int main(int argc, char *argv[]){
int sockfd, newsockfd, portno, clilen,pid, portNum, peerNum, csockfd, ssockfd;
struct sockaddr_in serv_addr, cli_addr;
char firstonline[5] = {'0'};
char msg[256];
bzero(msg, 256);
portNum = getPortNo();
peerNum = getPeerNo(portNum);
//asks if they are the first online.  If yes, set up server side and wait
int amIFirst = 0;
while (amIFirst != 1 || amIFirst !=2){
	amIFirst = firstOnline();
	if (amIFirst == 1){
		printf("you are hosting\n");
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd <0)
			error("ERROR opening socket");
		bzero((char *) &serv_addr, sizeof(serv_addr));
				portno = portNum;
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr))<0)
		error("ERROR on binding");
		listen(sockfd, 5);
		clilen = sizeof(cli_addr);
		while (1){
			
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		printf("Incoming call!\n");
		if (newsockfd <0) error("ERROR on accept");
		pid = fork();
		if (pid <0) error("ERROR on fork");
		if (pid ==0) { close(sockfd);
		
		dostuff(newsockfd);
		exit(0);
		}
		else close(newsockfd);
		}
		return 0;
	}else if (2 == amIFirst){
		printf("attempting to connect server port %d peer %d\n", portNum, peerNum);
		csockfd = connectServer(portNum, peerNum);
		char msg[256];
		bzero(msg, 256);
		while (msg[0] !='1'){
			printf("scanning from user\n");
		scanf("%s", msg);	//step 1 get message from user
		printf("writing to socket %s\n", msg);
		write(csockfd, msg, 256);//step 2 write message to socket
				
		printf("reading from socket\n");
		bzero(msg, 256);
		while (msg[0] != 0}
		read(msg, csockfd , 256);	//step 5 read from socket
		}

		break;
	}
	return 0;
}
//set up client side

return 1;
}

int connectServer(int portNum, int peerNum){
char host[20] = "localhost";
int sockfd =0;
struct hostent *server;
struct sockaddr_in serv_addr;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd <0) error("Error opening socket");
server = gethostbyname(host);
if (server == NULL){
	error("ERROR no such host'n");
}
bzero((char*)&serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
serv_addr.sin_port = htons(peerNum);
if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0)
		error("ERROR connecting");
		return sockfd;

}

void dostuff(int sock){
	printf("dostuff\n");
	int n;
	char buffer[256]= {0};
	char b[256];
	bzero(buffer, 256);
	bzero(b, 256);

	int k =0;
	while (k==0){
		printf("reading from socket\n");
	n = read(sock, buffer, 256);				//step 3 read from socket
	if (n <0) error("ERROR readign from socket");
	
	printf("username %d: %s\n",sock, buffer);
	printf("scanning from user\n");
	scanf("%s", &b);
	printf("writing to socket %s\n", b);
	write(sock, b, 256);			//step 4 write to socket
	if (b[0] == 'q') k = 1;		//quits conversation
	}
	}

//asks user if they're the first online
int firstOnline(){
	char str[5];
	int n = 0;
	while (n == 0){
	printf("enter 1 if first online.  else enter 2\n");
	scanf("%s", &str);
	n=atoi(str);
}
	return n;
}
//takes username and turns it into a port number
int getPortNo(){
	char str[5]= {'s'};
	printf("enter your name\n");
	scanf("%s", &str);
	int n = (int)str[0] + (int)str[1] + (int)str[2]+4000;
	while (n >6000) n -=1000;
	return n;
}
//takes peer's user name and turns it into a port number
int getPeerNo(int portno){;
	char str[5] = {'o'};
	int n = 0;
	while (n == 0 || n == portno){
	printf("enter peer name\n");
	scanf("%s", &str);
        n = (int)str[0] + (int)str[1] + (int)str[2] + 4000;
	while (n >6000) n -= 1000;
	}
	return n;
}

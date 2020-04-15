//junk1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//function prototypes
int recieveMsg(int portNumber);
int peerIsOnline(int peerPortNumber);
void putSelfOnline();	//opens server under user's port number
void connectToPeer(int peerPortNumber, int portNumber);	//tries to connect to peer
int  getPeerName(int portNumber);	//converts user input to peer port number
int dostuff(int sock);
int getSelfName();
void sendMessage(int peerno);
int main( int argc, char* argv[]){
	char str[10];
	int portNumber = getSelfName();
	int peerNumber = getPeerName(portNumber);
	//loops forever
	while(1){
	printf("Enter_1_to_listen_Enter_2_to_send_message\n");
	str[0] = '1';
	fgets(str, 10, stdin);
	fgets(str, 10, stdin);
	
	if (str[0] =='1')	
	putSelfOnline(portNumber);
	else if(str[0] =='2'){
		sendMessage(peerNumber);
	}
	}
	return 0 ;
}

void sendMessage(int peerno){
	
	write(peerno, "sending a message.  Please accept it\n", 50);
	printf("send message called\n ");
	return;
}
int getSelfName(){
	//user name of client
	char userName[255]={'0'};//zeros out username
	int portNumber = 5000;	//port number without username
	printf("Enter a user name\n");	//asks for username
	//sum of first 3 letters is the defaul in ASCII + 5000 is the default port number
	scanf("%s", userName);	
	portNumber += (int)userName[0] + (int) userName[1] + (int) userName[2];	
	return portNumber;
}

/**
 * checks to see if peer is online
 * returns -1 if offline
 * returns 1 if online
 * */
int peerIsOnline(int peerPortNumber){
printf("peerIsOnline\n");
//must see if port is in use	
    char host[20]= "localhost";
    char port[10];
    int portNum = -1;
    int sockfd = 0;
    struct hostent *server;
    struct sockaddr_in serv_addr;
    //user input for port and host
    portNum = peerPortNumber;
    printf("you want to connect to %d\n", portNum); 
    if (portNum <= 0){
       herror("\nInvalid Port Number\n");}
    //attempt connection
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        herror("Error opening socket");
    server = gethostbyname(host);
    if (server == NULL){
        herror("ERROR no such host\n");}
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portNum);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        herror("ERROR connecting");
    return sockfd;
}

/*
 * is given host's port Number
 * asks user for peer's name
 * converts peer's name into port number
 * returns peer's port number
 * */
int getPeerName(int portNumber){
	int peerPortNumber =5000;
	//listens for peer's username
	while (peerPortNumber == 5000 || peerPortNumber == portNumber){
	peerPortNumber = 5000;				//resets peerPortNumber
	printf("Who do you want to connect to?\n");	//asks client for peer's username
	char peerName[256] ={'0'};
	scanf("%s", peerName);
	//creates peer's port number
	peerPortNumber += (int)peerName[0] + (int) peerName[1] + (int) peerName[2];
	//printf("peer number %d", peerPortNumber);
	}
	return peerPortNumber;
}

void putSelfOnline(int portNumber){
//opens server on port number
int sockfd, newsockfd, portno, clilen, pid;
struct sockaddr_in serv_addr, cli_addr;
char msg[256]={'0'};
/*if (argc <2){	//tries to read socket number from input
	fprintf(stderr, "ERROR, no port provided\n");
	exit(1);
}*/
sockfd = socket(AF_INET, SOCK_STREAM,0);
if (sockfd < 0){
	herror("ERROR opening socket\n");
}

bzero((char *) &serv_addr, sizeof(serv_addr));
portno = portNumber;	//gets portNumber from user
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
if (bind(sockfd, (struct sockaddr *) &serv_addr,
			sizeof(serv_addr)) < 0){
	perror("ERROR on binding");
}//is the socket in use?
listen(sockfd, 5);
clilen = sizeof(cli_addr); 
//listens for connection??


//dummy variable
int counter = 0;
while (1) {
	printf("Waiting for peer to send a message\n");
	//getPeerName(portno);
	newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
	printf("newsockfd %d\n", newsockfd);
	if (newsockfd <0)
		perror("ERROR on accept");
	pid = fork();
	if (pid <0)
		perror("ERROR on fork");
	if (pid ==0){
		printf("alpha\n");
		close(sockfd);
		dostuff(newsockfd);
		exit(0);	
	} else close(newsockfd);
	counter++;
}
}

//reads and writes from socket
int dostuff(int peerPortNumber){
	printf("dostuff\n");
int n;
char buffer[256]={'0'};
char b[256]={'0'};
bzero(buffer, 256);
bzero(b, 256);
n = read(peerPortNumber, buffer, 256);//reads from peer's socket
if (n<0) error("ERROR reading from socket");

}

//connects client to peer 
//ASKER IS THE SERVER
//Client implements server functions
void connectToPeer(int peerPortNumber, int portNumber){
	int i=0;
	char msg[256] = {0};
	while(1 == peerIsOnline(peerPortNumber) && i < 3){
		printf("Enter Message for your friend\n");
		fgets( msg, 256, stdin);
		//send message
//		printf("You entered %s\n", msg);
		//if (msg[0] == '1') i = 3;
		recieveMsg(peerPortNumber);
		write(portNumber, msg,256);
	}
	printf("That user is not online\n");
	
//opens a port with default port number
//tests that peer is online
//sends 'hello world'
}

//terminates connection to Peer
//attempts to read from portNumber
//return 1 if there is a messagef
int recieveMsg(int portNumber){
	//attempts to read from socket
int i = 0;
char buffer[256]={'0'};
char b[256];
bzero(b, 256);
while ( read(portNumber, buffer, 256) < 0 && i < 5){
//if (n<0) herror("ERROR reading from socket");
++i;
}
if (buffer[0] == '0')
	return -1;
else{
	printf("Got message: %s\n", buffer);
	return 1;
	}
}

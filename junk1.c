//junk1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int recieveMsg(int portNumber);	//function prototype
int peerIsOnline(int portNumber);	//sends request to port
void putSelfOnline(int portNumber);	//opens server under user's port number
void connectToPeer(int peerPortNumber, int portNumber);	//tries to connect to peer
int getPeerName();			//converts user input to peer port number
//start program here
int main( int argc, char* argv[]){
	//user name of client
	char userName[255]={'0'};//zeros out username
	int portNumber = 5000;//port number without username
	int peerPortNumber = 5000;	//peer port number

	
	//asks for username
	printf("Enter a user name\n");
	//sum of first 3 letters is the defaul in ASCII + 5000 is the default port number
	scanf("%s", userName);	
	portNumber += (int)userName[0] + (int) userName[1] + (int) userName[2];
	
	//puts self online
	putSelfOnline(portNumber);

	return 0 ;
}

/**
 * checks to see if peer is online
 * returns -1 if offline
 * returns 1 if online
 * */
int peerIsOnline(int portNumber){
//must see if port is in use	
    char host[20]= "localhost";
    char port[10];
    int portNum = -1;
    int sockfd = 0;
    struct hostent *server;
    struct sockaddr_in serv_addr;

    if (portNumber <= 0)
    {
        herror("\nInvalid Port Number\n");
    }
    //attempt connection
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    if (sockfd < 0)
        herror("Error opening socket\n");
    server = gethostbyname(host);
    if(server == NULL){
        herror("ERROR no such host\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portNum);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    { 
     	return 1;
    }
    //return sockfd;
	return -1;

}

/*
 * is given host's port Number
 * asks user for peer's name
 * converts peer's name into port number
 * returns port number
 * */
int getPeerName(int portNumber){
	int peerPortNumber=5000;
	//listens for peer's username and connects is possible
	do{	//TODO fix this line to list for connection
	
	peerPortNumber = 5000;				//resets peerPortNumber
	printf("Who do you want to connect to?\n");	//asks client for peer's username
	char peerName[256] = {'0'};			//peer's name is zero'd out
	scanf("%s", peerName);				//scans peer's name from user
	peerPortNumber += (int)peerName[0] + (int) peerName[1] + (int) peerName[2]; //finds peer's port number

	if (recieveMsg(peerPortNumber) ==1)
		printf("someone is trying to talk to you");


	if (peerPortNumber != portNumber)		//prevents connection with self
		connectToPeer(peerPortNumber, portNumber);		//connects to peer and communicates until end of session
	if (recieveMsg(peerPortNumber) == 1)
		printf("someone passed you a note");
//	runs until user enters their own name
	} while ( peerPortNumber == portNumber );

	return peerPortNumber;
}

void putSelfOnline(int portNumber){
//opens server on port number

int sockfd, newsockfd, portno, clilen, pid;
struct sockaddr_in serv_addr, cli_addr;

if (portNumber <2){
	fprintf(stderr, "ERROR, no port provided\n");
	exit(1);
}
sockfd = socket(AF_INET, SOCK_STREAM,0);
if (sockfd < 0){
	herror("ERROR opening socket\n");
	
}

bzero((char *) &serv_addr, sizeof(serv_addr));
portno = portNumber;
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
while (counter <10) {
	newsockfd = getPeerName(portNumber);
	if (newsockfd <0)
		perror("ERROR on accept");
	pid = fork();
	if (pid <0)
		perror("ERROR on fork");
	if (pid ==0){
		close(sockfd);
	printf("Connection successful\n");
	} else close(newsockfd);
	counter++;
}
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

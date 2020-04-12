#include <stdio.h>
#ifndef c2
#include "client2.c"
#endif
#ifndef s2
#include "server2.c"
#endif

int recieveMsg(int portNumber);	//function prototype

//start program here
int main( int argc, const char* argv[]){
	//user name of client
	char* userName;
	
	//asks for username
	printf("Enter a user name");
	//userName in ASCII + 5000 is the default port number
	
	//asks client who they want to talk to
	//connects client to desired peer
	
	return 0;
}

//connects client to peer 
//ASKER IS THE SERVER
//Client implements server functions
void connetToPeer(char* peerName){
//opens a port with default port number
//tests that peer is online
//sends 'hello world'
}

//terminates connection to Peer
int recieveMsg(int portNumber){
	printf("recieveMsg called.  Terminating now.\n");//debugging line

	return -1;	//returns -1 as a flag to disconnect the server
}

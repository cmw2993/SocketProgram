/*
 * Server.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: cmw2993
 */

#include "Server.h"
#include <sys/socket.h> //include for socket info
#include <sys/socket.h> //used to make sockets
#include <unistd.h> //used to write and read functions
#include <string> //include for strings
#include <string.h> //used for strcat and strncmp
#include <signal.h> //used for handling signals
#include <iostream> //used for cout
#include <iomanip> //used for files
#include "LogFile.h" //logfile use
#include "Pages.h" //used to print the pages
#include <poll.h>
#include <fcntl.h>
Server::Server() {
	// TODO Auto-generated constructor stub

}

Server::~Server() {
	// TODO Auto-generated destructor stub
}
int Server::CreateSocket() {

	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //make a socket
	return sockfd; //Return previously made socket
}

int Server::bindSocket(int socket, int port) {
	struct sockaddr_in address; //create a sockaddr struct

	memset(&address, 0, sizeof(address)); //allocate memory to struct
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	int result = bind(socket, (struct sockaddr *) &address, sizeof(address)); //binding socket

	return result; //returning int for error check
}
int Server::listenSocket(int socket, int n) {
	int result = listen(socket, n); //listen to socket
	return result; //return int for error checking
}
int acceptConnection(int sockfd, struct sockaddr_in client_addr,
		socklen_t client_addr_len) {

	int clientfd = accept(sockfd, (struct sockaddr *) &client_addr,
			(unsigned int *) &client_addr_len); // using accept to get connection

	//Return clientfd
	return clientfd;
}
int Server::readSocket(int clientfd) {

	char read_buffer[65535]; //char to read socket
	int result = read(clientfd, read_buffer, 65534); //read the socket


	return result; //return int for error check


}
std::string Server::ReadPageChecker(int clientfd) {
	std::cout << "in readpagechecker"<<std::endl<<std::flush;

	int Result = fcntl(clientfd, F_SETFL, O_NONBLOCK);
	//use poll to wait for data to read
	//      initialize the file descriptor list
	//      there can be many int the list but
	//      there is only one herr
	struct pollfd	polllist[1];
	//      set the socket to pool
	polllist[0].fd		= clientfd;
	//      POLLIN is event when data is
	//      available to read
	polllist[0].events 	= POLLIN;

	// wait for data to read
	//      poll can timeout and
	//      return an error so you
	//      will have to check for these
	 Result = poll( polllist, 1, 10000 );

	std::string reader; //create string reader
	while (true) { //loop until error is created from running out of chars
		// initialize the buffer
		std::cout << "in loop"<<std::endl<<std::flush;
		char Buffer[256];
		memset(Buffer, 0, sizeof(Buffer));

		// read in a chunk
		int BytesRead = read(clientfd, Buffer, sizeof(Buffer) - 1);

		// check for an error
		if (-1 == BytesRead)
			break;


		reader += std::string(Buffer); //cast c strings to c++ strings

	}
	std::cout << errno << std::endl << std::flush;
	std::cout <<reader << "this";
	return reader; //return string

}
int Server::stringChecker(std::string str1) { //method to check for /status
	std::stringstream Work(str1); //convert str1 to stringstream
	std::string Checker1; //initialize variables
	std::string Checker2;
	Work >> Checker1 >> Checker2; //assigning value to strings
	if (Checker2 == "/status") //comparing the two strings while ignoring case
		return (1);

	if (Checker2 == "/dir") //check for dir
		return (2);

	return 0; //return 0 for error page

}
void Server::SignalHandling(int argc) {
	try {
		LogOpen(); //open log file
		int portNum = 9007; //set portnum to class arguments

		int socketFD; //socket fd variable
		Server Socket; //create instance of socket
		std::cout << "creating socket" << std::endl << std::flush; //print message to console
		LogMessages("creating socket\n"); //store message in logfile

		socketFD = Socket.CreateSocket(); //create socket
		if (socketFD == -1) { //check for errors

			std::cout << "error creating socket" << std::endl; //prompt user if there is an error
			LogMessages("Error creating Socket\n"); //store message in file
		}
		int bind; //creating variable for bind error check

		std::cout << "binding socket" << std::endl << std::flush; //print message to console
		LogMessages("binding socket\n"); //store message in file

		bind = Socket.bindSocket(socketFD, portNum); //bind socket
		if (bind == -1){ //checking for error
			std::cout << "error binding socket"<< std::endl <<std::flush; //informing user of error
			LogMessages("Error binding socket\n"); //store message in file
		}
		int listen; //creating variable to check for error listening

		std::cout << "listening socket" << std::endl << std::flush; //print message to the console
		LogMessages("Listening to Socket\n"); //store message in log file

		listen = Socket.listenSocket(socketFD, 5); //listening to socket
		if (listen == -1){ //error check
			std::cout << "error listening to socket" <<std::endl << std::flush; //informing user of error
			LogMessages("Error listening to socket\n"); //store message in logfile
		}

		struct sockaddr_in client_addr; //create struct for client address
		socklen_t client_addr_len; //create struct for client address length

		std::cout << "accepting connections" << std::endl << std::flush; //print message to console
		LogMessages("Accepting connection\n"); //store message in logfile
		while(true){ //loop to continue accepting connections

		int clientfd = accept(socketFD, (struct sockaddr *) &client_addr,
				(unsigned int *) &client_addr_len); //accept connection
		if (clientfd == -1) //error check
			std::cout << "error accepting connection"; //prompt user of error

		std::cout << "connection accepted: "<< clientfd << std::endl << std::flush; //print message to console
		LogMessages("Connection accepted\n"); //store message in logfile

		int result; //create error checking variable


		 //store log message
		std::cout << "calling read page checker"<<std::endl<<std::flush;

		std::string readBuf; //initialize variable
		readBuf = ReadPageChecker(clientfd); //get the socket read information
		LogMessages(readBuf);
		int pageVal = stringChecker(readBuf); //check to see what the user entered

		std::cout << "after stringChecker: "<<pageVal<<std::endl<<std::flush;

		Pages page; //create object page
		page.pageScan(pageVal, client_addr, clientfd, readBuf); //scan the pages

		//
		// *********************************
		//
		//	added this and it now works
		//		the page is send even if
		//		the buffer is not full
		//
		// *********************************
		//
		close( clientfd );
		//
		// *********************************
		//

		}
	} catch (...) { //catch exceptions
		std::cerr << "An exception has occurred" << std::endl;
		LogMessages("An Exception has occurred\n"); //log message
	}
}

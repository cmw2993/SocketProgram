/*
 * Server.h
 *
 *  Created on: Nov 14, 2017
 *      Author: cmw2993
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <sys/socket.h> //used to make sockets
#include <unistd.h> //used to write and read functions
#include <string> //used for strings
#include <signal.h> //used for handling signals
#include <iostream> //usd for cout
#include <iomanip> //used for files
#include "LogFile.h" // parent

class Server : public LogFile {
public:
	Server();
	virtual ~Server();
	int CreateSocket(); //method to create socket
	int bindSocket(int socket, int port); //method to bind socket
	int listenSocket(int socket, int num); //method to listen to socket
	int acceptConnection(int sockfd, struct sockaddr_in client_addr, //method to accept connection
			socklen_t client_addr_len);
	int readSocket(int clientfd); //method to read the socket
	int write(int clientfd,std::string buffer); //method to write the socket
	int stringChecker(std::string); //method to check the read
	void SignalHandling(int argc); //method to make all of these methods come together
	std::string ReadPageChecker(int clientfd);


};

#endif /* SERVER_H_ */

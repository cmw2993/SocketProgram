/*
 * Pages.h
 *
 *  Created on: Nov 14, 2017
 *      Author: cmw2993
 */

#ifndef PAGES_H_
#define PAGES_H_
#include <netinet/in.h> //used for computer address information
#include <sys/socket.h> //used to make sockets
#include <stdio.h> // used for printf, and File
#include <unistd.h> //used to write and read functions
#include <sys/utsname.h> //used to get kernel information
#include <errno.h> //used for errors
#include <sys/sysinfo.h> //used to get system information
#include <string> //used for strcat and strncmp
#include <time.h> //used to get system time
#include <arpa/inet.h> //used to get address
#include <signal.h> //used for handling signals
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <iomanip>
#include "LogFile.h"
class Pages : public LogFile {
public:
	Pages();
	virtual ~Pages();
	void statusPage(int clientfd, struct sockaddr_in client_addr);
	void errorPage(int clientfd);
	void pageScan(int pageVal, struct sockaddr_in client_addr, int clientfd, std::string read);
};

#endif /* PAGES_H_ */

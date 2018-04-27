/*
 * Pages.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: cmw2993
 */

#include "Pages.h"
#include <string> //used for strcat and strncmp
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Error.h"
#include "Status.h"
#include "Dir.h"

Pages::Pages() {
	// TODO Auto-generated constructor stub

}

Pages::~Pages() {
	// TODO Auto-generated destructor stub
}

void Pages::pageScan(int pageVal, struct sockaddr_in client_addr, int clientfd,
		std::string read) { //method to find and write the page requested

	std::cout << "in pageScan: "<<pageVal<<std::endl<<std::flush;


	char *reader = strdup(read.c_str()); //changing string to char pointer
	if (pageVal == 0) {

		Error f; //using polymorphism to create child object
		f.makePage(clientfd); //make the error page

	}
	if (pageVal == 1) {
		Status s; //using polymorphism to a child object
		s.WriteStatus(client_addr, clientfd); //write the status page

	}
	if (pageVal == 2) {
		Dir dir; //using polymorphism to create child object
		dir.dirRequest(clientfd, reader); //print the directory page
		//dir.WriteDir(clientfd, reader);
	}

}

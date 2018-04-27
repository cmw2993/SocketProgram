/*
 * Dir.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: cmw2993
 */

#include "Dir.h"
#include <string> //used for strings
#include <unistd.h> //used to write and read functions
#include <netinet/in.h>
#include <string.h> //used for cstrings
#include <unistd.h>
#include "LogFile.h"
#include <bits/stdc++.h>
#include <vector>


Dir::Dir() {
	// TODO Auto-generated constructor stub

}

Dir::~Dir() {
	// TODO Auto-generated destructor stub
}

std::string Dir::dirRequest(int clientfd, std::string readBuffer) { //method to read the user request
	char userRequest[65535];
	int tracker = 0;
	std::vector<std::string> tokens;
	std::stringstream str;
	for(int i = 0; i < readBuffer.length(); i++){
		if(i < readBuffer.length()){
		userRequest[i] = readBuffer.at(tracker);
		tracker++;
		userRequest[i+1] = ' ';
		i++;
		}
	}

	char *userRequestCont = strtok(NULL, " ");

	char *userRequestCont2 = strtok(userRequestCont, "r");
	char *endPath = strtok(NULL, " ");
	std::string endPath2 = endPath;
	LogMessages(endPath2);

	return endPath2;
}
int WriteDir(int clientfd, std::string endPath) {

	//buffers for writing to the webpage
	std::string buffer;
	std::string otherBuffer[65535];
	int bytes_written;

	struct dirent **namelist;
	struct stat StatBuffer;

	//for iterating through the directories
	int fileCount;
	int count = 0;

	fileCount = scandir(endPath, &namelist, NULL, alphasort);

	if (-1 == fileCount) {
		std::cout << "error reading directory" << std::endl << std::flush;
	}



	buffer = "HTTP/1.1 200 OK\r\n";
	/* write the message */
	bytes_written = write( clientfd, buffer.c_str(), buffer.length() );


	/* copy in a message */
	buffer = "Server: PAHWeb v1.0\r\n";
	/* write the message */
	bytes_written = write( clientfd, buffer.c_str(), buffer.length() );


	/* copy in a message */
	buffer = "Content-Type: text/html\r\n";
	/* write the message */
	bytes_written = write( clientfd, buffer.c_str(), buffer.length() );


	/* copy in a message */
	buffer = "\r\n";
	/* write the message */
	bytes_written = write( clientfd, buffer.c_str(), buffer.length() );


	/* copy in a message */
	buffer =
			"<html><head><title>Directory</title></head><body><h1>";
	/* write the message */
	bytes_written = write( clientfd, buffer.c_str(), buffer.length() );


	//prints the directories
	while (count < fileCount) {

		stat(endPath, &StatBuffer);

		if (S_ISDIR(StatBuffer.st_mode)) {

			sprintf(otherBuffer, "<a href = 'dir/%s> %s <a/> <br />", endPath,
					namelist[count]->d_name);

		}
		if (!S_ISDIR(StatBuffer.st_mode)) {

			sprintf(otherBuffer, "%s <br />", namelist[count]->d_name);
		}

		/* write the message */
		bytes_written = write(clientfd, otherBuffer, 65534);

		count++; //increment count
	}

	/* copy in a message */
	buffer = "</h1></body></html>";
	/* write the message */
	bytes_written = write( clientfd, buffer.c_str(), buffer.length() );


	std::cout << bytes_written << std::endl;

	return 0;
}

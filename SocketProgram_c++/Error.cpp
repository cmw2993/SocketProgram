/*
 * Error.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: cmw2993
 */

#include "Error.h"
#include <unistd.h> //used to write and read functions
#include <string>
Error::Error() {
	// TODO Auto-generated constructor stub

}

Error::~Error() {
	// TODO Auto-generated destructor stub
}

void Error::makePage(int clientfd) { //error page to be called if error presents itself

	std::cout << "in makePage:"<< clientfd <<std::endl<<std::flush;

	/* declare variables to use */
	std::string buffer;
	//in error page
	//setting buffer to the html code and writing it to the socket for the socket



	buffer = "HTTP/1.1 404 Not Found\r\n";
	int bw = write( clientfd, buffer.c_str(), buffer.length() );

	std::cout << "write: "<< buffer << " - " << bw << " - " <<errno <<std::endl<<std::flush;


	buffer = "Server: PAHWeb v1.0\r\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "\r\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "<html>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "   <title>PAHWeb Error Page</title>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "   <style>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "   body { background-color: yellow; }\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "   </style>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "</head>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "<body>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "   <h3>Error Page</h3>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "   <p>Invalid request for <strong>";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "</strong> HTTP Method and <strong>";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "</strong> Command.\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "<body>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	buffer = "<html>\n";
	write( clientfd, buffer.c_str(), buffer.length() );
	LogMessages("Page created. \n");

}

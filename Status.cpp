/*
 * Status.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: cmw2993
 */
#include <netinet/in.h>
#include "Status.h"
#include <string> //used for strings
#include <unistd.h> //used to write and read functions
#include <sstream> //used for string streams


Status::Status() {
	// TODO Auto-generated constructor stub

}

Status::~Status() {
	// TODO Auto-generated destructor stub
}

void Status::WriteStatus(struct sockaddr_in client_addr, int clientfd){
	struct utsname unameInfo; // Used for Kernel information
		uname(&unameInfo);

		struct sysinfo info; //Used for system information
		sysinfo(&info);

		time_t timer; // timer
		// setting timer to null to get rid of previous settings
		std::ostringstream stream; // String Stream variable for system info
		std::string time = asctime(localtime(&timer)); //set writebuffer to current time

		stream
				<< //set value of buffer to info
				"Total ram is " << info.totalram << " <br> Free ram is "
				<< info.freeram << "<br> Buffer Ram is " << info.bufferram
				<< "<br> Free high is " << info.freehigh
				<< "<br> Your processes are " << info.procs
				<< "<br> Your free swap is " << info.freeswap << "<br>"
				<< "Your loads are " << info.loads << "<br>Your Mem Unit is "
				<< info.mem_unit << "<br>Your pad is " << info.pad
				<< "<br>Your shared ram is " << info.sharedram
				<< "<br> Your total high is " << info.totalhigh
				<< "<br> Your total swap is " << info.totalswap << "<br>"
				<< " Your uptime is " << info.uptime << "<br> Your node name is "
				<< unameInfo.nodename << "<br> Your system name is "
				<< unameInfo.sysname << "<br>Your kernel version is "
				<< unameInfo.version << "<br>" << "Machine info "
				<< unameInfo.machine << "<br>Your release is " << unameInfo.release
				<< "<br>Your Network Address address is "
				<< inet_ntoa(client_addr.sin_addr)
				<< "<br> The date and time are %s" << time;
		std::string buffer2;
		buffer2 = stream.str();
		std::string buffer;
		//in status page
		buffer = "HTTP/1.1 Status Page\r\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "Server: PAHWeb v1.0\r\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "\r\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "<html>\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "   <title>PAHWeb Status Page</title>\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "   <style>\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "   body { background-color: SkyBlue; }\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "   </style>\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "</head>\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "   <h3>Status Page</h3>\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer = "<body> \n";
		write( clientfd, buffer.c_str(), buffer.length() );
		write( clientfd, buffer2.c_str(), buffer2.length() );
		buffer = "</body>\n";
		write( clientfd, buffer.c_str(), buffer.length() );
		buffer =  "</html>\n";
		write(clientfd, buffer.c_str(), buffer.length());
		LogMessages("Page created.\n");

}

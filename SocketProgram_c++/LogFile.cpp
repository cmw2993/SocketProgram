/*
 * LogFile.cpp
 *
 *  Created on: Nov 14, 2017
 *      Author: cmw2993
 */

#include "LogFile.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <fstream>

std::ofstream LogFile::logFile;

LogFile::LogFile() {
	// TODO Auto-generated constructor stub

}

LogFile::~LogFile() {
	// TODO Auto-generated destructor stub
}

void LogFile::LogMessages(std::string Message){
	auto CurrentTime = std::chrono::system_clock::to_time_t( //creating clock for time
			std::chrono::system_clock::now());
	struct tm LocalTime; //creating time struct

	localtime_r(&CurrentTime, &LocalTime);

	std::stringstream Timestamp; //creating stringstream

	Timestamp << std::put_time(&LocalTime, "[%Y-%m-%d %H:%M:%S]"); //puting year month day hour minute and second

	std::cout<<Timestamp.str() << " " << Message <<std::endl; //printing the message

	if(logFile.is_open() ) //checking to see if the file is open
		logFile<<Timestamp.str()<<" " << Message << std::endl << std::flush; //add message to file

	return;
}

void LogFile::LogOpen()
{
	if(!logFile.is_open()) //check to maek sure log file isn't open
		logFile.open("LogFile.txt"); // open the text file

	return;
}

void LogFile::LogClose()
{
	if(logFile.is_open()) //checking to make sure logfile is currently open
		logFile.close(); //closing the logfile

	return;
}





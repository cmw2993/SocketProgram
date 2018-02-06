/*
 * LogFile.h
 *
 *  Created on: Nov 14, 2017
 *      Author: cmw2993
 */

#ifndef LOGFILE_H_
#define LOGFILE_H_

#include <string>

class LogFile {
public:
	LogFile();
	virtual ~LogFile();
	void LogMessages(std::string Message);
	void LogOpen();
	void LogClose();
private:
	static std::ofstream logFile;
};

#endif /* LOGFILE_H_ */

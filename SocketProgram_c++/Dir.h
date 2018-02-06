/*
 * Dir.h
 *
 *  Created on: Nov 30, 2017
 *      Author: cmw2993
 */

#ifndef DIR_H_
#define DIR_H_
#include <string.h> //used for strcat and strncmp
#include "Pages.h"
#include "LogFile.h"
class Dir : public Pages { //extend pages
public:
	Dir();
	virtual ~Dir();
	std::string dirRequest(int clientfd, std::string readBuffer); //method to check the dir request
	int WriteDir(int clientfd, std::string endPath); //method to write the directory
};

#endif /* DIR_H_ */

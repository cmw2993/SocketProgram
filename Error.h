/*
 * Error.h
 *
 *  Created on: Nov 30, 2017
 *      Author: cmw2993
 */

#ifndef ERROR_H_
#define ERROR_H_
#include <unistd.h> //used to write and read functions
#include "Pages.h"
class Error : public Pages {
public:
	Error();
	virtual ~Error();
	void makePage(int clientfd);
};

#endif /* ERROR_H_ */

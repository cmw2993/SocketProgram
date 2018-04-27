/*
 * Status.h
 *
 *  Created on: Nov 30, 2017
 *      Author: cmw2993
 */

#ifndef STATUS_H_
#define STATUS_H_
#include "Pages.h"
class Status : public Pages {
public:
	Status();
	virtual ~Status();
	void WriteStatus(struct sockaddr_in client_addr, int clientfd);

};

#endif /* STATUS_H_ */

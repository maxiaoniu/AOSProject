/* 
 * File:   CMPWUtils.h
 * Author: mayue
 *
 * Created on March 30, 2015, 3:14 PM
 */

#ifndef CMPWUTILS_H
#define	CMPWUTILS_H

#include <string>
#include <sys/socket.h>

class CMPWUtils
{
public:
	static std::string getIpAndPort(const struct sockaddr* addr);
	static bool setnonblocking(int fd);
};

#endif	/* CMPWUTILS_H */


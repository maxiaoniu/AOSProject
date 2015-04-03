/* 
 * File:   CMPWEvent.h
 * Author: mayue
 *
 * Created on March 30, 2015, 7:52 PM
 */

#ifndef CMPWEVENT_H
#define	CMPWEVENT_H
#include <sys/epoll.h>

typedef int Event;
#define ACCEPT_EVENT  EPOLLIN
#define CONNECT_EVENT  EPOLLOUT
#define READ_EVENT EPOLLIN
#define WRITE_EVENT  EPOLLOUT


#endif	/* CMPWEVENT_H */


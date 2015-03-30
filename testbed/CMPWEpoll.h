/* 
 * File:   CMPWEpoll.h
 * Author: mayue
 *
 * Created on March 29, 2015, 8:01 PM
 */

#ifndef CMPWEPOLL_H
#define	CMPWEPOLL_H

#include<sys/epoll.h>
class CMPWEpoll {
public:
    CMPWEpoll(const int socket);
    ~CMPWEpoll();
    
    int addToEpoll(const int);
    int removeFromEpoll();
    int isListenEpoll(const int);
private:
    int m_epollFd;
    int m_socketFd;
    struct epoll_event m_epollEvent;
    struct epoll_event m_returnEpollEvents[1024];

    int epollCreate(const int socket);

};

#endif	/* CMPWEPOLL_H */


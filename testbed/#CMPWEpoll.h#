/* 
 * File:   CMPWEpoll.h
 * Author: mayue
 *
 * Created on March 29, 2015, 8:01 PM
 */

#ifndef CMPWEPOLL_H
#define	CMPWEPOLL_H
#include <map>
#include <sys/epoll.h>
#include "CMPWEvent.h"
#include "CMPWEventHandle.h"
class CMPWEpoll {
public:
    CMPWEpoll();
    ~CMPWEpoll();
    
    int waitEvent(std::map<Handle, CMPWEventHandle *> & handlers, int timeout = -1) ;
    int regEvent(Handle handle, Event evt) ;
    int removeEvent(Handle handle) ;
private:
    int m_epollFd;
    int m_fdCount;
};

#endif	/* CMPWEPOLL_H */


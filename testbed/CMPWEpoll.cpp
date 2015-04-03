/* 
 * File:   CMPWEpoll.cpp
 * Author: mayue
 * 
 * Created on March 29, 2015, 8:01 PM
 */

#include<vector>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<iostream>
#include <errno.h>
#include "CMPWEpoll.h"
#include "CMPWEvent.h"

CMPWEpoll::CMPWEpoll():m_fdCount(0) {
    m_epollFd = epoll_create(1024);
}

CMPWEpoll::~CMPWEpoll() {
    close(m_epollFd);    
}

int CMPWEpoll::regEvent(Handle handle, Event evt) {
    struct epoll_event ev;
    ev.data.fd = handle;
    
    ev.events = evt;
    if ( 0 != epoll_ctl( m_epollFd, EPOLL_CTL_ADD, handle, &ev ) )
    {
        if ( errno == ENOENT ) 
        {
            if ( 0 != epoll_ctl( m_epollFd, EPOLL_CTL_ADD, handle, &ev ) )
            {
                std::cerr << "epoll_ctl error:" << strerror(errno) << std::endl;
                return -errno;
            }
            ++m_fdCount;
        }
    }
    else
        ++m_fdCount;
    return 0;
}

int CMPWEpoll::waitEvent(std::map<Handle, CMPWEventHandle*> &handlers, int timeout) {
    std::vector<struct epoll_event> evs(m_fdCount);
    int num = epoll_wait(m_epollFd, &evs[0], m_fdCount, timeout);
    if (num > 0) {
        for (int i = 0; i < num; ++i) {
            Handle handle = evs[i].data.fd;

            if (EPOLLIN == evs[i].events) {
                handlers[ handle ]->readHandle();
            }
            if (EPOLLOUT == evs[i].events) {
                handlers[ handle ]->writeHandle();
            }

        }
    } else if (num < 0) {
        std::cerr << "epoll_wait error:" << strerror(errno) << std::endl;
    }

    return num;
}

int CMPWEpoll::removeEvent(Handle handle) {
    struct epoll_event ev;

    if (0 != epoll_ctl(m_epollFd, EPOLL_CTL_DEL, handle, &ev)) {
        std::cerr << "epoll_del error:" << strerror(errno) << std::endl;
        return -1;
    }

    --m_fdCount;
    return 0;
}
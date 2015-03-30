/* 
 * File:   CMPWEpoll.cpp
 * Author: mayue
 * 
 * Created on March 29, 2015, 8:01 PM
 */

#include "CMPWEpoll.h"
#include<vector>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<iostream>

CMPWEpoll::CMPWEpoll(const int socket) {
    epollCreate(socket);
}

CMPWEpoll::~CMPWEpoll() {
}

int CMPWEpoll::epollCreate(const int socket) {
    if(-1 == (m_epollFd = epoll_create(1024)))
    {
            return -1;
    }
    m_socketFd = socket;
    return 0;
}

int CMPWEpoll::addToEpoll(const int socket)
{
    memset(&m_epollEvent, 0, sizeof(m_epollEvent));

    m_epollEvent.events = EPOLLIN;
    m_epollEvent.data.fd = socket;

    if(-1 == epoll_ctl(m_epollFd, EPOLL_CTL_ADD, socket, &m_epollEvent))
    {
            return -1;
    }
    return 0;
}

int CMPWEpoll::isListenEpoll(const int socket)
{

    std::vector<int> vecListen;
    memset(&m_returnEpollEvents, 0, sizeof(m_returnEpollEvents));

    int readNum = epoll_wait(m_epollFd, m_returnEpollEvents, 1024, -1);
    std::cout << readNum << std::endl;

    for(int i = 0;i != readNum;++i)
    {
            if(m_returnEpollEvents[i].events & EPOLLIN && m_returnEpollEvents[i].data.fd == socket)
            {
                    int cliAccept = accept(m_returnEpollEvents[i].data.fd, NULL, NULL);
                    std::cout << "a new client online" << std::endl;
                    memset(&m_epollEvent, 0, sizeof(m_epollEvent));

                    m_epollEvent.events = EPOLLIN;
                    m_epollEvent.data.fd = cliAccept;

                    if(-1 == epoll_ctl(m_epollFd, EPOLL_CTL_ADD, cliAccept, &m_epollEvent))
                    {
                            return -1;
                    }

                    return cliAccept;
            }
            else if(m_returnEpollEvents[i].events & EPOLLIN)
            {
            //	epoll_ctl(_epollFd, EPOLL_CTL_DEL, _returnEpollEvents[i].data.fd, NULL);


                    return m_returnEpollEvents[i].data.fd;
            }

    }
}
/* 
 * File:   CMPWListenHandle.cpp
 * Author: mayue
 * 
 * Created on March 30, 2015, 2:06 PM
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include "CMPWEvent.h"
#include "CMPWListenHandle.h"
#include "CMPWUtils.h"
#include "CMPWEventHandle.h"
#include "CMPWReactor.h"
//#include "CMPWSocketIOHandle.h"

CMPWListenHandle::CMPWListenHandle(int fd):m_listen_fd(fd){
   
    memset( &clientAddr, 0, sizeof(clientAddr) );
}


CMPWListenHandle::~CMPWListenHandle() {
    close(m_listen_fd);

}

void CMPWListenHandle::readHandle() {


    socklen_t len;
    memset( &clientAddr, 0, sizeof(clientAddr) );

    int fd = accept(m_listen_fd, (struct sockaddr *)&clientAddr, &len);

}


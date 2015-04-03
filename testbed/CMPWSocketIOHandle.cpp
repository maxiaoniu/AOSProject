/* 
 * File:   CMPWSocketIOHandle.cpp
 * Author: mayue
 * 
 * Created on March 30, 2015, 11:56 PM
 */

#include "CMPWSocketIOHandle.h"
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>


#include "CMPWEventHandle.h"
#include "CMPWReactor.h"
#include "CMPWListenHandle.h"

CMPWSocketIOHandle::CMPWSocketIOHandle(Handle fd, std::vector<int> *fdList):m_socketFd(fd), m_fdList(fdList), m_packet(new PACKET) {
    memset( m_packet, 0, sizeof(PACKET) );
}

CMPWSocketIOHandle::~CMPWSocketIOHandle() {
    close( m_socketFd );
    delete[] m_packet;
}

void CMPWSocketIOHandle::readHandle()
{
    if ( 0 < read( m_socketFd, m_packet, sizeof(PACKET) ) )
    {
        std::cout<<(int)m_packet->src<<"--->" <<(int)m_packet->destination<<std::endl;
        std::cout<< "The cmd is "<<(int)m_packet->cmd <<std::endl;
        write(m_fdList->at(m_packet->destination), m_packet, sizeof(PACKET) );
    }
    
}

Handle CMPWSocketIOHandle::getHandle() const
{
    return m_socketFd;
}

void CMPWSocketIOHandle::writeHandle()
{
    
}
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
#include "CMPWCommand.h"
#include "CMPWTimerHandle.h"

CMPWSocketIOHandle::CMPWSocketIOHandle(Handle fd, TestbedOption* tb) : m_socketFd(fd), m_tb(tb), m_packet(new PACKET) {
    memset(m_packet, 0, sizeof (PACKET));
}

CMPWSocketIOHandle::~CMPWSocketIOHandle() {
    close(m_socketFd);
    delete[] m_packet;
}

void CMPWSocketIOHandle::readHandle() {
    TestCase *tc = m_tb->getCurrentTestCase();
    if (0 < read(m_socketFd, m_packet, sizeof (PACKET))) {
        //std::cout<<(int)m_packet->src<<"--->" <<(int)m_packet->destination<<std::endl;
        printNodeCmd(m_packet->src, m_packet->destination, m_packet->cmd);
        //std::cout<< "The cmd is "<<(int)m_packet->cmd <<std::endl;
        //if cmd destination is other nodes
        if(m_packet->destination != 0)
        {
            m_tb->m_msgCount++;
            write(m_tb->clientFdList->at(m_packet->destination), m_packet, sizeof (PACKET));
        }
        else
        {
            if(m_packet->cmd == CMD_ENTERED)
            {
                struct timeval tv;
                gettimeofday(&tv, NULL);
                tc->endTime[m_packet->src-1]=tv;
                tc->finish++;
                
            }
                        
        }
    }

}

Handle CMPWSocketIOHandle::getHandle() const {
    return m_socketFd;
}

void CMPWSocketIOHandle::writeHandle() {

}

void CMPWSocketIOHandle::printNodeCmd(char src, char des, char cmd) {
    printf("\x1b[%dm\x1b[%dm%2d\x1b[39m\x1b[49m", 32, 49, src);
    printf("-->");
    printf("\x1b[%dm\x1b[%dm%2d\x1b[39m\x1b[49m", 32, 49, des);
    printf("  ");

    switch (cmd) {
        case CMD_ASK_ENTER:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 34, 49, "[ASK NODE ENTER]");
            break;
        case CMD_END:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 34, 49, "[END]");
            break;
        case CMD_ENTERED:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 31, 49, "[HAVE ENTERED]");
            break;
        case CMD_EXITED:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 31, 49, "[HAVE EXITED]");
            break;
        case CMD_HOLDER:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 34, 49, "[YOU ARE HOLDER]");
            break;
        case CMD_INITIALIZATON:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 34, 49, "[INITIALIZATON]");
            break;
        case CMD_QUORUM:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 34, 49, "[QUORUM]");
            break;
        case CMD_REQUEST:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 34, 49, "[REQUEST]");
            break;
        case CMD_START:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 34, 49, "[START]");
            break;
        case CMD_TOKEN:
            printf("\x1b[%dm\x1b[%dm%s\x1b[39m\x1b[49m", 34, 49, "[TOKEN]");
            break;
    }
    printf("\n");
}


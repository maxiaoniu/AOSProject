/* 
 * File:   CMPWSocketIOHandle.h
 * Author: mayue
 *
 * Created on March 30, 2015, 11:56 PM
 */

#ifndef CMPWSOCKETIOHANDLE_H
#define	CMPWSOCKETIOHANDLE_H
#include <vector>
#include "CMPWEventHandle.h"
#include "CMPWPacket.h"
#include "TestbedOption.h"

class CMPWSocketIOHandle : public CMPWEventHandle {
public:
    CMPWSocketIOHandle(Handle fd, TestbedOption* tb);
    virtual ~CMPWSocketIOHandle();
    
    virtual Handle getHandle() const;
    virtual void readHandle();
    virtual void writeHandle();
    
private:
    Handle m_socketFd;
    TestbedOption* m_tb;
    PACKET* m_packet;
    static const int MAX_SIZE = 1024; 
    void printNodeCmd(char src, char des, char cmd);
};
#endif	/* CMPWSOCKETIOHANDLE_H */


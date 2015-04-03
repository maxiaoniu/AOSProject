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
class CMPWSocketIOHandle : public CMPWEventHandle {
public:
    CMPWSocketIOHandle(Handle fd, std::vector<int> *fdList);
    virtual ~CMPWSocketIOHandle();
    
    virtual Handle getHandle() const;
    virtual void readHandle();
    virtual void writeHandle();
    
private:
    Handle m_socketFd;
    std::vector<int> *m_fdList;
    PACKET* m_packet;
    static const int MAX_SIZE = 1024;
};

#endif	/* CMPWSOCKETIOHANDLE_H */


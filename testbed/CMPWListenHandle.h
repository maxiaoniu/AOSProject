/* 
 * File:   CMPWListenHandle.h
 * Author: mayue
 *
 * Created on March 30, 2015, 2:06 PM
 */

#ifndef CMPWLISTENHANDLE_H
#define	CMPWLISTENHANDLE_H

#include "CMPWEventHandle.h"
#include <sys/socket.h>
class CMPWListenHandle : public CMPWEventHandle {
public:
    CMPWListenHandle(int fd);
    virtual ~CMPWListenHandle();
    virtual Handle getHandle() const { return m_listen_fd; }
    virtual void readHandle();
    virtual void writeHandle() {}

private:
    Handle m_listen_fd;
    struct sockaddr clientAddr;

};

#endif	/* CMPWLISTENHANDLE_H */


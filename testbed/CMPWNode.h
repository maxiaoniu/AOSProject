/* 
 * File:   CMPWNode.h
 * Author: mayue
 *
 * Created on April 1, 2015, 9:49 PM
 */

#ifndef CMPWNODE_H

#include <sys/socket.h>
#include <string>
#include <vector>

#include "CMPWEventHandle.h"
class CMPWNode {
public:
    CMPWNode();
    virtual ~CMPWNode();
    void init(int fd);
    unsigned int clientIpAddr;
    std::string clientHostName;
    char nodeID;
    std::vector<int> *clientFdList;
private:
    int m_clientFd;
    //CMPWEventHandle *m_ioHandle;
    
};

#endif	/* CMPWNODE_H */


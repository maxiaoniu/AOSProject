/* 
 * File:   CMPWNode.cpp
 * Author: mayue
 * 
 * Created on April 1, 2015, 9:49 PM
 */

#include "CMPWNode.h"
#include "CMPWReactor.h"
#include "CMPWPacket.h"
#include "CMPWSocketIOHandle.h"
#include <sys/socket.h>
#include <string.h>
CMPWNode::CMPWNode() {
    nodeID = 0;
}


CMPWNode::~CMPWNode() {
    //if(m_ioHandle!=NULL)
      //  delete m_ioHandle;
}

void CMPWNode::init(int fd) {
    //set id to remote node
    PACKET *packet = new PACKET;
    bzero(packet, sizeof (PACKET));
    packet->destination = nodeID;
    write(fd, packet, sizeof (PACKET));
    delete packet;
    //register handle to reactor
    CMPWEventHandle *h = new CMPWSocketIOHandle(fd, clientFdList );
    CMPWReactor& r = CMPWReactor::getInstance();
    r.regEvent(h, READ_EVENT);
}

/* 
 * File:   main.cpp
 * Author: mayue
 *
 * Created on March 27, 2015, 4:20 PM
 */

#include <iostream>
#include <cstring>
#include <stdint.h>
#include <vector>
#include "TestbedOption.h"
#include "CMPWSocket.h"
#include "CMPWEventHandle.h"
#include "CMPWListenHandle.h"
#include "CMPWReactor.h"
#include "CMPWEvent.h"
#include "CMPWUtils.h"
#include "CMPWNode.h"
#include "CMPWPacket.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  
    cout << "start" << endl;
  
    TestbedOption tb("system.ini","testbed.ini");
    tb.parse();
    tb.printConfiguration();
    CMPWSocket serverTB;
    
    if(-1 == serverTB.tcpServer(2222)) {
        return 0;
    }
    int n;

    n = tb.m_nodesNumber;
    vector<CMPWNode> nodeList(n+1);
    vector<int> clientFdList(n+1);
    while (n > 0) {
        struct sockaddr_in sin;
	socklen_t len = sizeof(struct sockaddr_in);
        uint32_t ip;
        int index;
        int clientFd;
        clientFd = serverTB.socketAccept((struct sockaddr *)&sin, &len);
        ip = sin.sin_addr.s_addr;
        index = (tb.m_IPmapNodeID).find(ip)->second;
        nodeList[index] = CMPWNode();
        nodeList[index].nodeID = (char)index;
        nodeList[index].clientIpAddr = ip;
        clientFdList[index] = clientFd;
        nodeList[index].clientFdList = &clientFdList;
        nodeList[index].init(clientFd);
        //set a index to node
        
        std::cout << "Node "<< index <<" is online!"<< std::endl;
        std::cout << "The address is " << CMPWUtils::getIpAndPort((struct sockaddr *) &sin) << std::endl;
        n--;
    }
    CMPWReactor &reactor = CMPWReactor::getInstance();
    //CMPWEventHandle* handler = new CMPWListenHandle(serverTB.m_listen_fd);
    //reactor.regEvent(handler, ACCEPT_EVENT);

    while( true )
    {
        reactor.eventLoop(-1); 
    }

    
    
    return 0;
}


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
#include "CMPWTimer.h"
#include "CMPWCommand.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    cout << "start" << endl;

    TestbedOption tb("system.ini", "testbed.ini");
    tb.parse();
    tb.printConfiguration();
    CMPWSocket serverTB;

    if (-1 == serverTB.tcpServer(2223)) {
        return 0;
    }
    int n;

    n = tb.m_nodesNumber;
    vector<CMPWNode> nodeList(n + 1);
    vector<int> clientFdList(n + 1);
    while (n > 0) {
        struct sockaddr_in sin;
        socklen_t len = sizeof (struct sockaddr_in);
        uint32_t ip;
        int index;
        int clientFd;
        clientFd = serverTB.socketAccept((struct sockaddr *) &sin, &len);
        CMPWUtils::setnonblocking(clientFd);
        ip = sin.sin_addr.s_addr;
        index = (tb.m_IPmapNodeID).find(ip)->second;
        nodeList[index] = CMPWNode();
        nodeList[index].nodeID = (char) index;
        nodeList[index].clientIpAddr = ip;
        clientFdList[index] = clientFd;
        nodeList[index].tb = &tb;
        nodeList[index].init(clientFd);
        //set a index to node

        std::cout << "Node " << index << " is online!" << std::endl;
        std::cout << "The address is " << CMPWUtils::getIpAndPort((struct sockaddr *) &sin) << std::endl;
        n--;
    }
    tb.clientFdList = &clientFdList;
    PACKET *packet = new PACKET;
    bzero(packet, sizeof (PACKET));
    for (int i = 1; i < tb.m_nodesNumber + 1; i++) {
        bzero(packet, sizeof (PACKET));
        if (tb.m_testMode == 1)
            packet->cmd = CMD_MEAKAWA;
        else
            packet->cmd = CMD_CMPW;
        packet->destination = i;
        write(clientFdList[i], packet, sizeof (PACKET));     
    }
    for (int i = 1; i < tb.m_nodesNumber+1; i++) {
        packet->cmd = CMD_QUORUM;
        packet->src = 0;
        packet->destination = i;
        std::copy(tb.quorumList[i-1].begin(),tb.quorumList[i-1].end(),packet->quorum);
        write(clientFdList[i], packet, sizeof (PACKET));
    }
    bzero(packet, sizeof (PACKET));
    packet->destination = tb.m_tokenHolder;
    packet->cmd = CMD_HOLDER;
    write(clientFdList[tb.m_tokenHolder], packet, sizeof (PACKET));
    for (int i = 1; i < tb.m_nodesNumber+1; i++) {     
        bzero(packet, sizeof (PACKET));
        packet->cmd = CMD_START;
        packet->destination = i;        
        write(clientFdList[i], packet, sizeof (PACKET));        
    }
    delete packet;

    CMPWReactor &reactor = CMPWReactor::getInstance();
    CMPWTimer timer(tb.m_timer,1000);

    timer.setTestBed(&tb);
    timer.start();

    while (true) {
        reactor.eventLoop(-1);
    }
    return 0;
}


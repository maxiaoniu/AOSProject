/* 
 * File:   main.cpp
 * Author: mayue
 *
 * Created on March 27, 2015, 4:20 PM
 */

#include <iostream>
#include <cstring>
#include <stdint.h>
#include "TestbedOption.h"
#include "CMPWSocket.h"
#include "CMPWEpoll.h"

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
    
    serverTB.tcpServer(2222);
    
    CMPWEpoll serverEpoll(serverTB.m_listen_fd);
    
    serverEpoll.addToEpoll(serverTB.m_listen_fd);
    int res;
    while(1)
    {
        res = serverEpoll.isListenEpoll(serverTB.m_listen_fd);
        if(res != -1)
        {
            std::cout << res << std::endl;
        }
    }
    
    return 0;
}


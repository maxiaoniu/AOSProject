/* 
 * File:   CMPWTimerHandle.cpp
 * Author: mayue
 * 
 * Created on April 4, 2015, 9:47 PM
 */

#include "CMPWTimerHandle.h"
#include "CMPWPacket.h"

#include "TestbedOption.h"
#include "CMPWCommand.h"
#include <sys/timerfd.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>     
#include <iostream>
CMPWTimerHandle::CMPWTimerHandle(int fd, TestbedOption* tb):m_timerFd(fd), m_tb(tb), m_timerCount(0),m_testcaseID(0),m_currentAlgo(1){
    
}

CMPWTimerHandle::~CMPWTimerHandle() {
}

void CMPWTimerHandle::readHandle() {

    m_testcase = m_tb->getCurrentTestCase();
    uint64_t exp;
    ssize_t s = read(m_timerFd, &exp, sizeof (uint64_t));
    if (m_testcase->finish==m_tb->m_nodesNumber) {
        m_timerCount = 0;
        m_testcaseID = m_testcaseID + 1;
        m_tb->m_currentTC++;
        m_testcase->finish = 0;
        std::cout<< "Testcase "<<m_testcaseID<<" is over."<<std::endl;
        printf("Amount message number: %d \n",m_tb->m_msgCount);
        m_tb->m_msgCount = 0;
        printTestCaseResult(m_testcase);  
        for (int i = 1; i < m_tb->m_nodesNumber+1; i++) {
            send(0,i,CMD_END);
        }
        if (m_testcaseID < m_tb->m_testcasesCount) {
            send(0, m_tb->m_tokenHolder, CMD_HOLDER);
            for (int i = 1; i < m_tb->m_nodesNumber + 1; i++) {
                send(0, i, CMD_START);
            }
        }//have finish one algorithm
        else {
            if (m_tb->algoNumber == 2) {
                if (m_currentAlgo == 1) {
                    std::cout<< "Meakawa's Algorithm test"<<std::endl;
                    m_tb->m_currentTC = 0;
                    m_currentAlgo++;
                    m_testcaseID = 0;
                    for (int i = 1; i < m_tb->m_nodesNumber + 1; i++) {
                        send(0, i, CMD_MEAKAWA);
                        PACKET *packet = new PACKET;
                        bzero(packet, sizeof (PACKET));
                        packet->cmd = CMD_QUORUM;
                        packet->src = 0;
                        packet->destination = i;
                        std::copy(m_tb->quorumList[i-1].begin(),m_tb->quorumList[i-1].end(),packet->quorum);
                        write((m_tb->clientFdList)->at(i), packet, sizeof (PACKET));
                        delete packet;
                        send(0, i, CMD_START);
                    }
                } else {
                    exit(1);
                }
            } else {
                exit(1);
            }

        }
        
    } else {
        m_timerCount = exp + m_timerCount;

        std::vector<int> client = (m_testcase->timerNode).find(m_timerCount - 1)->second;
        struct timeval tv;
        gettimeofday(&tv, NULL);
        for (std::vector<int>::iterator it = client.begin(); it != client.end(); ++it) {
            std::cout<<"node"<< *it << " ";
            send(0,*it,CMD_ASK_ENTER);
            m_testcase->startTime[(*it)-1] = tv;
        }
        std::cout<< "are asked enter critical section"<<std::endl;

    }
}

 void CMPWTimerHandle::printTestCaseResult(TestCase *tc)
 {

    for (int i = 0; i < m_tb->m_nodesNumber; i++) {
        //std::cout << "node" << i + 1 << ":";
        //printf("start time:%ld.%ld ", tc->startTime[i].tv_sec, tc->startTime[i].tv_usec);
        //printf("end time:%ld.%ld ", tc->endTime[i].tv_sec, tc->endTime[i].tv_usec);
        //printf("\r\n");
        printf("node%2d: %6.2f ms",i+1,((tc->endTime[i].tv_sec - tc->startTime[i].tv_sec)*1000000L+ tc->endTime[i].tv_usec - tc->startTime[i].tv_usec)/1000.0);
        printf("\n");
    }

     
 }
 
 void CMPWTimerHandle::send(char src, char des, char cmd) {
        PACKET *packet = new PACKET;
        bzero(packet, sizeof (PACKET));
        packet->src = src;
        packet->destination = des;
        packet->cmd = cmd;
        write((m_tb->clientFdList)->at(des), packet, sizeof (PACKET));
        delete packet;
 }
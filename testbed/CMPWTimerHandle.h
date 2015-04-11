/* 
 * File:   CMPWTimerHandle.h
 * Author: mayue
 *
 * Created on April 4, 2015, 9:47 PM
 */

#ifndef CMPWTIMERHANDLE_H
#define	CMPWTIMERHANDLE_H
#include "CMPWEventHandle.h"
#include "TestbedOption.h"
#include <vector>
#include <map>
class TestbedOption;
class CMPWTimerHandle : public CMPWEventHandle {
public:
    CMPWTimerHandle(int fd, TestbedOption* tb);
    virtual ~CMPWTimerHandle();
    virtual int getHandle() const { return m_timerFd; }
    virtual void readHandle();
    virtual void writeHandle() {}
private:
    int m_timerFd;
    TestbedOption* m_tb;
    int m_timerCount;
    int m_testcaseID;
    int m_currentAlgo;
    TestCase *m_testcase;
    
    void printTestCaseResult(TestCase *tc);
    void send(char src, char des, char cmd);
};

#endif	/* CMPWTIMERHANDLE_H */


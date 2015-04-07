/* 
 * File:   TestbedOption.h
 * Author: mayue
 *
 * Created on March 27, 2015, 10:49 PM
 */

#ifndef TESTBEDOPTION_H
#define	TESTBEDOPTION_H
#include "INI.h"
#include <vector>
#include <map>
#include <sys/time.h>

struct testcase {
    std::map<int, std::vector<int> > timerNode;
    std::vector<timeval> startTime;
    std::vector<timeval> endTime;
    int finish;
};
typedef testcase TestCase;
typedef std::vector<char> Quorum;
class TestbedOption {
public:

    TestbedOption(const std::string &sysParaFileName,const std::string &tbParaFileName);
    virtual ~TestbedOption();
    
    int m_nodesNumber; //the number of nodes in the system
    int m_timer;        //the period of test case
    int m_testcasesCount;
    int m_testMode;     //1: maekawa’s algorithm 2: our own algorithm 3: both
    int m_tokenHolder;
    std::vector<int> *clientFdList;
    std::vector<int> m_nodeIDList;
    std::vector<Quorum> quorumList;
    //system parameters
    std::map<int,uint32_t> m_nodeIDmapIP;
    std::map<uint32_t,int> m_IPmapNodeID;
    
    int m_ctlPort;
    int m_nodePort;
    int m_currentTC;
    int m_msgCount;
    bool parse();
    void printConfiguration();
    TestCase *getCurrentTestCase();
    
private:
    std::string m_sysParaFileName;
    std::string m_tbParaFileName;
    
    bool parseSystemPara();
    bool parseTestbedPara();        
    uint32_t getIPfromHost(const std::string &host);
    std::vector<int> splitString(const std::string &s, const std::string &seperator);
    std::vector<TestCase> m_testcases;
    
    void devide_quorum(int n);
    
};

#endif	/* TESTBEDOPTION_H */


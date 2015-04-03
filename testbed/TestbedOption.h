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

class TestbedOption {
public:
    TestbedOption(const std::string &sysParaFileName,const std::string &tbParaFileName);
    virtual ~TestbedOption();
    
    int m_nodesNumber; //the number of nodes in the system
    int m_timer;        //the period of test case
    int m_testcasesCount;
    int m_testMode;     //1: maekawa’s algorithm 2: our own algorithm 3: both
    int m_tokenHolder;
    std::vector<int> m_nodeIDList;
    //system parameters
    std::map<int,uint32_t> m_nodeIDmapIP;
    std::map<uint32_t,int> m_IPmapNodeID;
    int m_ctlPort;
    int m_nodePort;
    
    bool parse();
    void printConfiguration();
    
private:
    std::string m_sysParaFileName;
    std::string m_tbParaFileName;
    bool parseSystemPara();
    bool parseTestbedPara();
    uint32_t getIPfromHost(const std::string &host);
    std::vector<int> splitString(const std::string &s, const std::string &seperator);
    

};

#endif	/* TESTBEDOPTION_H */


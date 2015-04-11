/* 
 * File:   TestbedOption.cpp
 * Author: mayue
 * 
 * Created on March 27, 2015, 10:49 PM
 */

#include "TestbedOption.h"
#include <iostream>
#include<sys/socket.h>
#include<errno.h> //For errno - the error number
#include<netdb.h> //hostent
#include<arpa/inet.h>
typedef INI<std::string, std::string, std::string> ini_t;

TestbedOption::TestbedOption(const std::string &sysParaFileName,const std::string &tbParaFileName):m_currentTC(0),m_msgCount(0) {
    
    m_sysParaFileName = sysParaFileName;
    m_tbParaFileName = tbParaFileName;        
}


TestbedOption::~TestbedOption() {
}

bool TestbedOption::parse() {
    
    return parseTestbedPara() & parseSystemPara();
}

void TestbedOption::printConfiguration()
{
    std::cout << "Open the configuration files successful" << std::endl;
    std::cout << "We have " << m_nodesNumber << " nodes: " << std::endl;
    for (std::vector<int>::iterator it = m_nodeIDList.begin() ; it != m_nodeIDList.end(); ++it)
    {
        std::cout<<"node"<< *it << " ";
        //std::cout << m_nodeIDmapIP.find(*it)->second<< std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "We have " << m_testcasesCount <<" test scases." << std::endl;
    switch(m_testMode)
    {
        case 1:
            std::cout<<"We will test maekawa’s algorithm."<< std::endl;
            break;
        case 2:
            std::cout<<"We will test our own CMPW algorithm."<< std::endl;
            break;
        case 3:
            std::cout<<"We will test maekawa’s algorithm and our CMPW algorithm."<< std::endl;
            break;
    }
}

bool TestbedOption::parseTestbedPara() {
    
    ini_t ini(m_tbParaFileName,false);
    if(!ini.parse()) 
    {
        std::cout << "Error: Can't open test bed configuration file: " + m_tbParaFileName;
        return false;
    }
    ini.select("system");
    m_nodesNumber = Converters::Convert<int>(ini.get("number","-1"));    
    m_nodeIDList = splitString(ini.get("nodes","-1"),",");
    //devide quorum
    devide_quorum(m_nodesNumber);
    ini.select("test");
    m_timer = Converters::Convert<int>(ini.get("timer","-1"));  
    m_testcasesCount = Converters::Convert<int>(ini.get("testcase_number","-1"));   
    m_testMode = Converters::Convert<int>(ini.get("algorithm_selection","-1")); 
    if(m_testMode==3)
        algoNumber=2;
    else
        algoNumber=1;
    m_tokenHolder = Converters::Convert<int>(ini.get("Token_holder","-1")); 
    // parse testcase
    for(int i=0; i < m_testcasesCount; i++)
    {
        std::stringstream str;
        int timerCount;
        TestCase tc;
        str << "testcase"<<(i+1);
        ini.select(str.str());
        timerCount = Converters::Convert<int>(ini.get("timer_number","-1"));
        for(int j=0; j < timerCount; j++)
        {
            
            str.str("");
            str << "t"<<(j+1);
            tc.timerNode.insert(std::pair<int, std::vector<int> >(j,splitString(ini.get(str.str(),"-1"),",")));
            
        }
        tc.finish = 0;
        tc.startTime.resize(m_nodesNumber);
        tc.endTime.resize(m_nodesNumber);
        m_testcases.push_back(tc);       
    }
    
    return true;
}

bool TestbedOption::parseSystemPara() {
    uint32_t ip;
    ini_t ini(m_sysParaFileName, false);
    if (!ini.parse()) {
        std::cout << "Error: Can't open system configuration file: " + m_sysParaFileName;
        return false;
    }
    //create the node index to IP map
    ini.select("address");
    for (ini_t::keysit_t i = ini.current->begin(); i != ini.current->end(); i++) {
        ip = getIPfromHost((std::string &)(i->second));
        if(ip<0)
            return false;
       
        m_nodeIDmapIP.insert(std::pair<int, uint32_t>(Converters::Convert<int>(i->first), ip));
        m_IPmapNodeID.insert(std::pair<uint32_t, int>(ip, Converters::Convert<int>(i->first)));
    }
    
    //parse the port
    ini.select("ports");
    m_ctlPort = Converters::Convert<int>(ini.get("Control","-1"));
    m_nodePort = Converters::Convert<int>(ini.get("Node","-1"));
            
    return true;

}

std::vector<int> TestbedOption::splitString(const std::string &s, const std::string &seperator) {

    std::vector<int> result;
    std::string::size_type pos1, pos2;
    pos2 = s.find(seperator);
    pos1 = 0;
    
    while(std::string::npos != pos2) {
        result.push_back(Converters::Convert<int>(s.substr(pos1,pos2-pos1)));
        
        pos1 = pos2 + seperator.size();
        pos2 = s.find(seperator,pos1);
        
    }
    
    if(pos1 != s.length()) {
        result.push_back(Converters::Convert<int>(s.substr(pos1)));
    }
    return result;
    
}

uint32_t TestbedOption::getIPfromHost(const std::string &host) {
        struct addrinfo hint;
        struct addrinfo *answer;

        memset(&hint, 0, sizeof(hint));
        hint.ai_family = AF_INET;
        hint.ai_socktype = SOCK_STREAM;

        int ret = getaddrinfo(host.c_str(), NULL, &hint, &answer);
        if(ret != 0)
        {
            std::cerr << "getaddrinfo error" << strerror(errno);
            return uint32_t(-1);
        }

        //we only use first find addr
        for(struct addrinfo* cur = answer; cur != NULL; cur = cur->ai_next)
        {
            return ((struct sockaddr_in*)(cur->ai_addr))->sin_addr.s_addr;
        }

        std::cerr<<"getHostByName Error";
        return uint32_t(-1);
}

TestCase *TestbedOption::getCurrentTestCase(){
    
     return &m_testcases[m_currentTC];
}

void TestbedOption::devide_quorum(int n) {
    int k = 1;
    while ((k * k) < n)
        k++;
    char matrix[k][k];
    char node = 1;

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (node <= n) {
                matrix[i][j] = node;
                node++;
            } else
                matrix[i][j] = -1;
        }
    }
    //devide the quorums
    for (int row = 0; row < k; row++) {
        for (int col = 0; col < k; col++) {
            Quorum q;
            //add the row element
            for (int idx = 0; idx < k; idx++) {
                if (matrix[row][idx] != -1)
                    q.push_back(matrix[row][idx]);
            }
            //add the column element
            for (int idx = 0; idx < k; idx++) {
                if (idx == row)
                    continue;
                else {
                    if (matrix[idx][col] != -1)
                        q.push_back(matrix[idx][col]);
                }
            }
            quorumList.push_back(q);
        }
    }
}
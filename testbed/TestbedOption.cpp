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

TestbedOption::TestbedOption(const std::string &sysParaFileName,const std::string &tbParaFileName) {
    
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
    std::cout << "Open the two files successful" << std::endl;
    std::cout << "We have " << m_nodesNumber << " nodes: " << std::endl;
    for (std::vector<int>::iterator it = m_nodeIDList.begin() ; it != m_nodeIDList.end(); ++it)
    {
        std::cout<<"node"<< *it << " ";
        //std::cout << m_nodeIDmapIP.find(*it)->second<< std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "We have " << m_testcasesCount <<" test scases." << std::endl;
    
    
    
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
    ini.select("test");
    m_timer = Converters::Convert<int>(ini.get("timer","-1"));  
    m_testcasesCount = Converters::Convert<int>(ini.get("testcase_number","-1"));   
    m_testMode = Converters::Convert<int>(ini.get("algorithm_selection","-1"));   
    m_tokenHolder = Converters::Convert<int>(ini.get("Token_holder","-1"));   
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
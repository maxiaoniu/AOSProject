/* 
 * File:   TestbedOption.cpp
 * Author: mayue
 * 
 * Created on March 27, 2015, 10:49 PM
 */

#include "TestbedOption.h"
#include <iostream>
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
        std::cout << *it << "--";
        std::cout << m_nodeIDmapIP.find(*it)->second<< std::endl;
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
    ini_t ini(m_sysParaFileName, false);
    if (!ini.parse()) {
        std::cout << "Error: Can't open system configuration file: " + m_sysParaFileName;
        return false;
    }
    //create the node index to IP map
    ini.select("address");
    for (ini_t::keysit_t i = ini.current->begin(); i != ini.current->end(); i++) {
        m_nodeIDmapIP.insert(std::pair<int, std::string>(Converters::Convert<int>(i->first), i->second));
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

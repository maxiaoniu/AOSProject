/* 
 * File:   CMPWReactor.cpp
 * Author: mayue
 * 
 * Created on March 30, 2015, 3:19 PM
 */

#include "CMPWReactor.h"
CMPWReactor CMPWReactor::reactor;

CMPWReactor& CMPWReactor::getInstance()
{
    return reactor;
}
CMPWReactor::CMPWReactor() {
    m_demultiplexer = new CMPWEpoll();
}

CMPWReactor::~CMPWReactor() {
    for (iterator it = m_handlers.begin(); it != m_handlers.end(); ++it) {
        delete it->second;
    }

    if (m_demultiplexer)
        delete m_demultiplexer;
}

int CMPWReactor::regEvent(CMPWEventHandle* handler, Event evt) {
    int handle = handler->getHandle();

    if (m_handlers.end() == m_handlers.find(handle)) {
        m_handlers.insert(std::make_pair<Handle, CMPWEventHandle *>(handle, handler));
    }

    return m_demultiplexer->regEvent(handle, evt);
}

void CMPWReactor::removeEvent(CMPWEventHandle* handler) {
    int handle = handler->getHandle();
    m_demultiplexer->removeEvent(handle);

    iterator it = m_handlers.find(handle);
    delete it->second;

    m_handlers.erase(handle);
}

void CMPWReactor::eventLoop(int timeout) {
    m_demultiplexer->waitEvent(m_handlers, timeout);
}
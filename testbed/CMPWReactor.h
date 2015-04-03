/* 
 * File:   CMPWReactor.h
 * Author: mayue
 *
 * Created on March 30, 2015, 3:19 PM
 */

#ifndef CMPWREACTOR_H
#define	CMPWREACTOR_H
#include <map>
#include "CMPWEventHandle.h"
#include "CMPWEvent.h"
#include "CMPWEpoll.h"
typedef std::map<Handle, CMPWEventHandle *>::iterator iterator;

class CMPWReactor {
public:
    CMPWReactor();
    virtual ~CMPWReactor();
    int regEvent(CMPWEventHandle * handler, Event evt);
    void removeEvent(CMPWEventHandle * handler);
    void eventLoop(int timeout = 0);
    static CMPWReactor& getInstance();
private:
    std::map<Handle, CMPWEventHandle *>  m_handlers;
    CMPWEpoll *m_demultiplexer;
    static CMPWReactor reactor;
};


#endif	/* CMPWREACTOR_H */


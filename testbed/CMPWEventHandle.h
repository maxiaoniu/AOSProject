/* 
 * File:   CMPWEventHandle.h
 * Author: mayue
 *
 * Created on March 30, 2015, 1:51 PM
 */

#ifndef CMPWEVENTHANDLE_H
#define	CMPWEVENTHANDLE_H

typedef int Handle;
class CMPWEventHandle {
public:
    CMPWEventHandle(){};
    virtual ~CMPWEventHandle(){};
    virtual Handle getHandle() const = 0;
    virtual void readHandle() = 0;
    virtual void writeHandle() = 0;  
    
private:

};

#endif	/* CMPWEVENTHANDLE_H */


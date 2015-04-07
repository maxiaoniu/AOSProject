/* 
 * File:   CMPWTimer.h
 * Author: mayue
 *
 * Created on April 4, 2015, 7:56 PM
 */

#ifndef CMPWTIMER_H
#define	CMPWTIMER_H
class TestbedOption;
class CMPWTimer {
public:
    CMPWTimer(int repeat, int after);
    virtual ~CMPWTimer();
    void reset(int repeat, int after);
    void start();
    void stop();
    void setTestBed(TestbedOption *tb){m_tb = tb; }
private:
    int m_fd;
    bool m_running;
    bool m_repeated;
    TestbedOption *m_tb;

};

#endif	/* CMPWTIMER_H */


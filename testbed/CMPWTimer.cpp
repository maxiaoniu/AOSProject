/* 
 * File:   CMPWTimer.cpp
 * Author: mayue
 * 
 * Created on April 4, 2015, 7:56 PM
 */


#include "CMPWReactor.h"
#include "CMPWEventHandle.h"
#include "CMPWEvent.h"
#include "CMPWTimer.h"
#include "CMPWTimerHandle.h"
#include "TestbedOption.h"
#include <sys/timerfd.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <iostream>


const uint64_t milliPerSeconds = 1000;
const uint64_t microPerSeconds = 1000000;
const uint64_t nanoPerSeconds = 1000000000;
const uint64_t nanoPerMilli = 1000000;


CMPWTimer::CMPWTimer(int repeat, int after) : m_running(false), m_repeated(false){  
    m_fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    if (m_fd < 0) {
        std::cerr<< "create timer error" << strerror(errno) <<std::endl;
        return;
    }

    reset(repeat, after);
}


CMPWTimer::~CMPWTimer() {
    if(m_fd >0)
    {
        close(m_fd);
    }        
}

void CMPWTimer::reset(int repeat, int after) {
    if (m_fd <= 0) {
        return;
    }

    m_repeated = (repeat > 0);

    struct itimerspec t;
    if (repeat > 0) {
        t.it_interval.tv_sec = (uint64_t) repeat / milliPerSeconds;
        t.it_interval.tv_nsec = ((uint64_t) repeat % milliPerSeconds) * nanoPerMilli;
    }

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    t.it_value.tv_sec = now.tv_sec + (uint64_t) after / milliPerSeconds;
    t.it_value.tv_nsec = now.tv_nsec + ((uint64_t) after % milliPerSeconds) * nanoPerMilli;

    if (timerfd_settime(m_fd, TFD_TIMER_ABSTIME, &t, NULL) < 0) {
        std::cerr<< "set timer error" << strerror(errno) <<std::endl;
    }
}

void CMPWTimer::start() {

    if (m_running) {
        std::cout<< "timer is running" << std::endl;
        return;
    }
    m_running = true;
    CMPWEventHandle *h = new CMPWTimerHandle(m_fd, m_tb);
    CMPWReactor& r = CMPWReactor::getInstance();
    r.regEvent(h, READ_EVENT);
}

void CMPWTimer::stop() {
    if (!m_running) {
        std::cout<< "timer had been stopped" << std::endl;
        return;
    }

    m_running = false;
    //m_loop->removeHandler(m_fd);

}
#ifndef _TIMERWHEEL_H
#define _TIMERWHEEL_H
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <thread>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <time.h>
#include <error.h>
#include <string.h>


struct param
{
    struct itimerspec its;
    int ifd;
};
struct TimerTask
{
    int repeat;
    int timeval;
    int id;
    std::function<void()> task;
};

class TimerWheel
{
public:
    TimerWheel(int tick = 5,int slot_num = (1<<3),int layer_num = (1<<4));
    ~TimerWheel();
    void Start();
    void Stop();
    int AddTask(struct TimerTask &task);

private:
    int init();
    void shedule(int);
    void tick();
private:
    int m_tick;
    int m_slot_num;
    int m_layer_num;
    int m_cur_slot_num;
    int m_cur_layer_num;
    int m_status;//0 = stop , 1 = running
    std::vector<std::vector<std::list<struct TimerTask>>> wheel;

    std::thread *m_run_shedule;
    int m_timer_fd;

};

#endif // !WHEEL_H

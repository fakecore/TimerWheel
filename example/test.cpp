

#include "../src/timerwheel.h"


int main(int argc,char **argv)
{
    TimerWheel tw(100);
    struct TimerTask task;
    task.repeat = 1;
    task.timeval = 500;
    task.task = std::bind([]{
        printf("hello\n");
    });
    tw.AddTask(task);
    tw.Start();


    while(1);
    return 0;
}
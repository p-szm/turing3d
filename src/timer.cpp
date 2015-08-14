//
//  timer.cpp
//  turing3d
//
//  Created by Patrick on 14/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#include "timer.h"
#include <sys/time.h>

void microsecond_time (unsigned long long &t)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    t = (unsigned long long)tv.tv_usec + 1000000 * (unsigned long long)tv.tv_sec;
}

Timer::Timer(double t_sec)
{
    interval = t_sec * 1000000;
}

bool Timer::is_done() const
{
    unsigned long long int curr_time;
    microsecond_time(curr_time);
    if ((curr_time - start_time) > interval)
        return true;
    return false;
}

double Timer::get_interval() const
{
    return interval / 1000000.0;
}

void Timer::set_interval(double t_sec)
{
    interval = t_sec * 1000000;
}

void Timer::reset()
{
    microsecond_time(start_time);
}

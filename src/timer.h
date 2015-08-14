//
//  timer.h
//  turing3d
//
//  Created by Patrick on 14/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__timer__
#define __turing3d__timer__

#include <stdio.h>

class Timer
{
public:
    Timer(double t_sec);
    bool is_done() const;
    double get_interval() const;
    void set_interval(double t_sec);
    void reset();
private:
    unsigned long long int start_time;
    unsigned long long int interval;
};

#endif /* defined(__turing3d__timer__) */

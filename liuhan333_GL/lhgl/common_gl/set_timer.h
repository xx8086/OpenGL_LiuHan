#ifndef COMMON_SET_TIME_H
#define COMMON_SET_TIME_H

#include <map>
#include "lhgl_config.h"

namespace lh_time {
    
    class CTimer
    {
    public:
        CTimer();
        virtual ~CTimer();

    public:
        unsigned int set_timeout(const function_time& cb, unsigned int dwTimeout);
        unsigned int set_interval(const function_time& cb, unsigned int dwTimeout);
    private:
        void clear_timer();
    };
}

#endif
#include "set_timer.h"
#include <Windows.h>

namespace lh_time {
    static std::map<unsigned int, function_time> s_timer_list;

    CTimer::CTimer()
    {}

    CTimer::~CTimer()
    {
        clear_timer();
    }

    void CALLBACK timeout_proc(
        HWND hwnd,
        UINT umsg,
        UINT_PTR id_event,
        DWORD detime)
    {
        ::KillTimer(hwnd, id_event);
        std::map< unsigned int, function_time >::iterator it = s_timer_list.find(id_event);
        if (it != s_timer_list.end())
        {
            const function_time cb = (*it).second;
            s_timer_list.erase(it);
            cb();
        }
    }

    void CALLBACK interval_proc(
        HWND hwnd,
        UINT umsg,
        UINT_PTR id_event,
        DWORD detime)
    {
        std::map< unsigned int, function_time >::iterator it = s_timer_list.find(id_event);
        if (it != s_timer_list.end())
        {
            const function_time cb = (*it).second;
            cb();
        }
    }

    unsigned int CTimer::set_timeout(const function_time& cb, unsigned int dwTimeout)
    {
        unsigned int dwTimer = 0;
#ifdef _WIN32
        dwTimer = SetTimer(NULL, 0, dwTimeout, &timeout_proc);
#else
#endif
        s_timer_list[dwTimer] = cb;
        return dwTimer;
    }

    unsigned int CTimer::set_interval(const function_time& cb, unsigned int dwTimeout)
    {
        unsigned int dwTimer = 0;
#ifdef _WIN32
        dwTimer = SetTimer(NULL, 0, dwTimeout, &interval_proc);
#else
#endif
        s_timer_list[dwTimer] = cb;
        return dwTimer;
    }

    void CTimer::clear_timer()
    {
        for (std::map< unsigned int, function_time >::iterator itTime = s_timer_list.begin();
            itTime != s_timer_list.end(); )
        {         
#ifdef _WIN32
            ::KillTimer(NULL, itTime->first);
#else
#endif
            itTime = s_timer_list.erase(itTime);
            if (itTime == s_timer_list.end())
            {
                break;
            }
        }
    }
}


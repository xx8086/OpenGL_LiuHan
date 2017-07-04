#pragma once

#include <Windows.h>
#include "singleton.h"
#include "set_timer.h"
#include "lhgl_render_base.h"

namespace lh_gl_interface {
    class LhGlInterfase :
        public Singleton<LhGlInterfase>
    {
    public:
        LhGlInterfase();
        virtual ~LhGlInterfase();
        SINGLE_LH(LhGlInterfase)
    public:
        int set_fps(function_time&, int);
        bool initialize(HDC);
        bool drew();
        bool relese();
        bool resize(unsigned short, unsigned short);
        bool lhgl_keyborad(bool, unsigned int, unsigned int);
        bool lhgl_mosuemove(unsigned int, unsigned int, unsigned int);
    private:
        bool set_pixel(HDC);
        bool set_glcontext(HDC);

    private:
        lh_time::CTimer timer;
        HGLRC hrc = nullptr;
        lh_gl::CGlRenderBase* _render = nullptr;
    };
}

#pragma once
#include "gl_example_pyramid.h"

namespace lh_gl {
    class CRanderExModelMX :
        public  CRanderExPyramid
    {
    public:
        virtual void do_render();
        virtual bool init();
    };
}
#ifndef GL_EXAMPLE_PYRAMID_H
#define	GL_EXAMPLE_PYRAMID_H
#include "gl_render.h"

namespace lh_gl {

    class CRanderExPyramid :
        public CRender
    {
    public:
        CRanderExPyramid():CRender() {};
        ~CRanderExPyramid();

    protected:
        virtual void render_bypipe();
        virtual void set_point_light();
        virtual void set_spot_light();
        virtual void set_directional_light();
    public:
        virtual void do_render();
        virtual bool init();
    };
}
#endif

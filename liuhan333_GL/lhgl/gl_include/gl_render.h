#ifndef GL_INCLUDE_GL_RANDER_H
#define	GL_INCLUDE_GL_RANDER_H
#include "gl_render_base.h"

namespace lh_gl {

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

    class CRender:
        protected CGlRenderBase
    {
    public:
        CRender();
        virtual ~CRender();
    public:
        void do_render();
        bool init();
        bool onmouse(unsigned int mark, unsigned int x, unsigned int y);
        bool specialkeyboard(bool, unsigned int, unsigned int);
    private:
        void render_scene_texture();
        void render_bypipe();
        void render_translation();
        void render_rotate();
        void render_scale();
        void render_triangle();

    private:
        float _fscale = 0.0f;
        const float FieldDepth = 20.0f;
    };
}
#endif
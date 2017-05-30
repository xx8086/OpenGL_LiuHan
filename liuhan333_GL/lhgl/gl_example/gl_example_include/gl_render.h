#ifndef GL_INCLUDE_GL_RANDER_H
#define	GL_INCLUDE_GL_RANDER_H
#include "lhgl_render_base.h"
#include "lhgl_mesh.h"

namespace lh_gl {

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

    class CRender:
        public CGlRenderBase
    {
    public:
        CRender();
        virtual ~CRender();
    public:
        void do_render();
        bool init();
        
    private:
        void render_scene_texture();
        void render_bypipe();
        void render_translation();
        void render_rotate();
        void render_scale();
        void render_triangle();

    protected:
        void init_shardes();
    private:
        bool init_texture();
        bool init_mesh();
        
    private:
        float _fscale = 0.0f;
        const float FieldDepth = 20.0f;
    private:
        CShardes* _gl_shardes = nullptr;
        Texture* _texture = nullptr;
        Mesh* _mesh = nullptr;
    };
}
#endif
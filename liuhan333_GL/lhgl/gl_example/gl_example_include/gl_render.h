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
        virtual void do_render();
        virtual bool init();
    private:
        void render_scene_texture();
        void render_translation(float);
        void render_rotate(float);
        void render_scale(float);
        void render_triangle(float);

    protected:
        virtual void render_bypipe() {};
        virtual void set_point_light() {};
        virtual void set_spot_light() {};
        virtual void set_directional_light() {};
        virtual void set_shardes(const char* , const char*);
    protected:
        bool set_texture(const char*);
        bool set_mesh(const char*);

    protected:
        CShardes* _gl_shardes = nullptr;
        float _fscale = 0.0f;
        const float FieldDepth = 20.0f;
    private:
        
        Texture* _texture = nullptr;
        Mesh* _mesh = nullptr;
    };
}
#endif
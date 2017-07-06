#pragma once
#include "gl_example_pyramid.h"

namespace lh_gl {
    class CRanderShadowMap :
        public CRanderExPyramid
    {
    public:
        CRanderShadowMap();
        virtual ~CRanderShadowMap();

    protected:
        virtual void render_bypipe();
        virtual void render_scene_texture();
        virtual void set_point_light() {};
        virtual void set_spot_light() ;
        virtual void set_directional_light() {};
        void render_second();
    private:
        void render_bypipe_framebuffer();
        void render_bypipe_frametexture();
        
    public:
        virtual void do_render();
        virtual bool init();
    private:
        SpotLight _spot_light;
        Mesh* _mesh_quad = nullptr;
    };

}

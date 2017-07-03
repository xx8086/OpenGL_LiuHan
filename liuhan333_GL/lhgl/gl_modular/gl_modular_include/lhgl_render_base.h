#ifndef GL_INCLUDE_GL_RENDER_BASE_H
#define	GL_INCLUDE_GL_RENDER_BASE_H
#include "gl_shardes.h"
#include "lhgl_camera.h"
#include "lhgl_image.h"
#include "lhgl_lights_common.h"
#include "lhgl_vertex_interface.h"


namespace lh_gl {

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

    class CGlRenderBase
    {
    public:
        CGlRenderBase();
        virtual ~CGlRenderBase();

    public:
        bool onmouse(unsigned int mark, unsigned int x, unsigned int y);
        bool specialkeyboard(bool, unsigned int, unsigned int);
        virtual void do_render() = 0;
        virtual bool init() = 0;
    protected:
        virtual void set_point_light() = 0;
        virtual void set_spot_light() = 0;
        virtual void set_directional_light() = 0;
        virtual void set_projection(float, float, float);
        virtual void set_main_directionlight(const Vector3f&, const Vector3f&, const float, const float);
        virtual void set_main_camera(const Vector3f&, const Vector3f&, const Vector3f&);
        void set_vertex(int, unsigned int*, int, VertexText*);

    protected:
        PersProjInfo _pers_projInfo;
        DirectionalLight _directionallight;
        Camera* _game_camera = nullptr;
        CGlVertexInterface* _gl_vertex = nullptr;
    };
}
#endif
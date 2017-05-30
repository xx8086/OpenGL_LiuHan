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

    public:
        virtual bool init();
    protected:
        virtual void init_shardes() = 0;
    private:
        void init_projection();
        void init_light();
        void init_vertex();
        void init_camera();

    protected:
        PersProjInfo _pers_projInfo;
        DirectionalLight _directionallight;
        Camera* _game_camera = nullptr;
        CGlVertexInterface* _gl_vertex = nullptr;
    };
}
#endif
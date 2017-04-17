#ifndef GL_INCLUDE_GL_RENDER_BASE_H
#define	GL_INCLUDE_GL_RENDER_BASE_H
#include "gl_shardes.h"
#include "lhgl_camera.h"
#include "lhgl_image.h"
#include "lhgl_lights_common.h"
#include "gl_vertex_interface.h"
#include "lhgl_mesh.h"

namespace lh_gl {

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

    class CGlRenderBase
    {
    public:
        CGlRenderBase();
        virtual ~CGlRenderBase();

    protected:
        void init_projection();
        bool init_texture();
        bool init_mesh();
        void init_camera();
        void init_light();
        void init_vertex();
        void init_shardes();
        
    private:
        void release();

    protected:
        PersProjInfo _pers_projInfo;
        DirectionalLight _directionallight;

        CGlVertexInterface* _gl_vertex = nullptr;
        CShardes* _gl_shardes = nullptr;
        Camera* _game_camera = nullptr;
        Texture* _texture = nullptr;
        Mesh* _mesh = nullptr;
    };
}
#endif
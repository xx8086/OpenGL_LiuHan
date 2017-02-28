#include "gl_render_base.h"
#include "base_config.h"

namespace lh_gl {

    CGlRenderBase::CGlRenderBase()
    {}
    CGlRenderBase::~CGlRenderBase()
    {
        release();
    }

    void CGlRenderBase::release()
    {
        DELETE_PTR(_game_camera)
        DELETE_PTR(_texture)
        DELETE_PTR(_gl_vertex)
    }

    void CGlRenderBase::init_projection()
    {
        _pers_projInfo.FOV = 60.0f;
        _pers_projInfo.Height = WINDOW_HEIGHT;
        _pers_projInfo.Width = WINDOW_WIDTH;
        _pers_projInfo.zNear = 1.0f;
        _pers_projInfo.zFar = 100.0f;
    }

    bool CGlRenderBase::init_texture()
    {
        DELETE_PTR(_texture)
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        _gl_shardes->gluniform_sampler_1i(0);
        _texture = new Texture(GL_TEXTURE_2D, "..\\res\\Content\\timg.jpg");
        if (!_texture->load_image())
        {
            return false;
        }
        return true;
    }
    
    void CGlRenderBase::init_camera()
    {
        DELETE_PTR(_game_camera)
        _game_camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT,
            Vector3f(0.0f, 0.0f, -3.0f), //pos
            Vector3f(0.0f, 0.0f, 1.0f), //target
            Vector3f(0.0f, 1.0f, 0.0f)); //up
    }

    void CGlRenderBase::init_light()
    {
        _directionallight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        _directionallight.AmbientIntensity = 0.01f;
        _directionallight.DiffuseIntensity = 0.75f;
        _directionallight.Direction = Vector3f(1.0f, 0.0f, 0.0f);
    }

    void CGlRenderBase::init_vertex()
    {
        DELETE_PTR(_gl_vertex)
        _gl_vertex = new CGlVertexInterface;
        _gl_vertex->create_vertex();
    }

    void CGlRenderBase::init_shardes()
    {
        DELETE_PTR(_gl_shardes);
        _gl_shardes = new lh_gl::CShardes;
        _gl_shardes->glsharde_init();
        _gl_shardes->uniformlocation();
    }
}
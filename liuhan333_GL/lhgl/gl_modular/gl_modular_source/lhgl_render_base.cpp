#include "lhgl_render_base.h"
#include "base_config.h"
#include "lhgl_key_trans.h"

namespace lh_gl {

    CGlRenderBase::CGlRenderBase()
    {}
    CGlRenderBase::~CGlRenderBase()
    {
        DELETE_PTR(_game_camera)
    }

    void CGlRenderBase::init_projection()
    {
        _pers_projInfo.FOV = 60.0f;
        _pers_projInfo.Height = WINDOW_HEIGHT;
        _pers_projInfo.Width = WINDOW_WIDTH;
        _pers_projInfo.zNear = 1.0f;
        _pers_projInfo.zFar = 100.0f;
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

    bool CGlRenderBase::init()
    {
        init_shardes();

        init_camera();
        init_light();
        init_vertex();        
        init_projection();

        return true;
    }

    bool CGlRenderBase::onmouse(unsigned int mark, unsigned int x, unsigned int y)
    {
        bool rt = false;
        if (lh_mouse_move(mark))
        {
            rt = _game_camera->om_mouse((int)x, (int)y);
        }
        return rt;
    }

    bool CGlRenderBase::specialkeyboard(bool bchar, unsigned int uchar, unsigned int utype)
    {
        LHGL_KEY key = lh_to_glkey(bchar, uchar);
        _game_camera->on_keyboard(key);
        _directionallight.on_keyboard(key);
        return true;
    }
}
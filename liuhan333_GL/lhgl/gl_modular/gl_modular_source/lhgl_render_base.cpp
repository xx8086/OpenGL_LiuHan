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

    void CGlRenderBase::set_projection(float fov, float znear, float zfat)
    {
        _pers_projInfo.Width = WINDOW_WIDTH;
        _pers_projInfo.Height = WINDOW_HEIGHT;
        _pers_projInfo.FOV = fov;// 60.0f;
        _pers_projInfo.zNear = znear;// 1.0f;
        _pers_projInfo.zFar = zfat;// 100.0f;
    }

    
    
    void CGlRenderBase::set_main_camera(const Vector3f& pos, const Vector3f& target, const Vector3f& up)
    {
        DELETE_PTR(_game_camera)
        _game_camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT,
            pos, target, up);
    }

    void CGlRenderBase::set_main_directionlight(const Vector3f& color, 
        const Vector3f& direction,
        const float ambient, 
        const float diffuse)
    {
        _directionallight.Color = color;
        _directionallight.Direction = direction;
        _directionallight.AmbientIntensity = ambient;
        _directionallight.DiffuseIntensity = diffuse;
    }

    void CGlRenderBase::set_vertex(int indices_nums, unsigned int* indices,
        int vertices_nums, VertexText* vertices)
    {
        DELETE_PTR(_gl_vertex)
        _gl_vertex = new CGlVertexInterface;
        _gl_vertex->set_vert_ind_ices(indices_nums, indices, vertices_nums, vertices);
        _gl_vertex->create_vertex();
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
#include "gl_render.h"
#include "lhgl_pipeline.h"
#include "gl_vertex_struct.h"
#include "lhgl_key_trans.h"


namespace lh_gl {

    CRender::CRender()
    {}

    CRender::~CRender()
    {}

    void CRender::do_render()
    {
        render_scene_texture();
    }

    void CRender::render_scene_texture()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        render_bypipe();

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, _gl_vertex->get_vbo());
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexText), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexText), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexText), (const GLvoid*)20);

        _texture->bind_image(GL_TEXTURE0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _gl_vertex->get_ibo());
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }

    void CRender::render_bypipe()
    {
        _fscale += 0.1f;
        Pipeline p;
        p.Rotate(_fscale, 0.0f, 0.0f);
        p.WorldPos(0.0f, 0.0f, -1.0f);
        p.SetPerspectiveProj(_pers_projInfo);// 设置投影变换的参数
        p.SetCamera(*_game_camera);
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, (const GLfloat*)p.GetWorldTrans().m);
        _gl_shardes->gluniform_wvp_matrix_4fv(1, GL_TRUE, (const GLfloat*)p.GetWVPTrans().m);
        _gl_shardes->gluniform_light(_directionallight);
    }
    void CRender::render_translation()
    {
        _fscale += 0.01f;
        float world[16] = {
            1.0f, 0.0f, 0.0f, sinf(_fscale),
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f };
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, (const GLfloat*)world);
    }

    void CRender::render_rotate()
    {
        _fscale += 0.01f;
        float sinscale = sinf(_fscale);
        float cosscale = cosf(_fscale);
        float world[16] = {
            cosscale,    0.0f,   -sinscale,   0.0f,
            0.0f,        1.0f,    0.0f,       0.0f,
            sinscale,    0.0f,    cosscale,   0.0f,
            0.0f,        0.0f,    0.0f,       1.0f };
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, (const GLfloat*)world);
    }

    void CRender::render_scale()
    {
        _fscale += 0.01f;
        float sinscale = sinf(_fscale);
        float world[16] = {
            sinscale,   0.0f,       0.0f,       0.0f,
            0.0f,       sinscale,   0.0f,       0.0f,
            0.0f,       0.0f,       sinscale,   0.0f,
            0.0f,       0.0f,       0.0f,       1.0f };
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, (const GLfloat*)world);
    }

    void CRender::render_triangle()
    {
        _fscale += 0.01f;
        _gl_shardes->gluniform_scale_1f(sinf(_fscale));
    }

    bool CRender::init()
    {
        init_camera();
        init_light();
        init_shardes();

        init_vertex();
        init_projection();
        init_texture();

        return true;
    }

    bool CRender::onmouse(unsigned int mark, unsigned int x, unsigned int y)
    {
        bool rt = false;
        if (lh_mouse_move(mark))
        {
            rt = _game_camera->om_mouse((int)x, (int)y);
        }
        return rt;
    }

    bool CRender::specialkeyboard(bool bchar, unsigned int uchar, unsigned int utype)
    {
        LHGL_KEY key = lh_to_glkey(bchar, uchar);
        _game_camera->on_keyboard(key);
        _directionallight.on_keyboard(key);
        return true;
    }
}
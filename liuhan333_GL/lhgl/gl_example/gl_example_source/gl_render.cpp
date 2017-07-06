#include "gl_render.h"

namespace lh_gl {

    CRender::CRender():CGlRenderBase()
    {}

    CRender::~CRender()
    {
        DELETE_PTR(_texture)
        DELETE_PTR(_gl_vertex)
        DELETE_PTR(_mesh)
    }

    void CRender::do_render()
    {
        render_scene_texture();
    }

    void CRender::render_scene_texture()
    {
        glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
        render_bypipe();

        _gl_shardes->gl_enable();
        
        if (_gl_vertex)_gl_shardes->gl_drawelements(_gl_vertex->get_vbo(), _gl_vertex->get_ibo());
        if (_texture)_texture->bind_image(GL_TEXTURE0);
        
        if (_mesh)_mesh->Render();
        
        _gl_shardes->gl_disable();
    }

    void CRender::render_translation(float trans)
    {
        //_fscale += 0.01f;
        float world[16] = {
            1.0f, 0.0f, 0.0f, sinf(trans),
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f };
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, (const GLfloat*)world);
    }

    void CRender::render_rotate(float rotate)
    {
        //_fscale += 0.01f;
        float sinrotate = sinf(rotate);
        float cosrotate = cosf(rotate);
        float world[16] = {
            cosrotate,    0.0f,   -sinrotate,   0.0f,
            0.0f,        1.0f,    0.0f,       0.0f,
            sinrotate,    0.0f,    cosrotate,   0.0f,
            0.0f,        0.0f,    0.0f,       1.0f };
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, (const GLfloat*)world);
    }

    void CRender::render_scale(float scale)
    {
        //_fscale += 0.01f;
        float sinscale = sinf(scale);
        float world[16] = {
            sinscale,   0.0f,       0.0f,       0.0f,
            0.0f,       sinscale,   0.0f,       0.0f,
            0.0f,       0.0f,       sinscale,   0.0f,
            0.0f,       0.0f,       0.0f,       1.0f };
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, (const GLfloat*)world);
    }

    void CRender::render_triangle(float scale)
    {
        //_fscale += 0.01f;
        _gl_shardes->gluniform_scale_1f(sinf(scale));
    }

    bool CRender::set_mesh(const char* meshfile)
    {
        DELETE_PTR(_mesh)
        glEnable(GL_DEPTH_TEST);
        _mesh = new Mesh();
        return _mesh->LoadMesh(meshfile);
    }

    bool CRender::set_mesh(Mesh*&  moremesh, const char* meshfile)
    {
        glEnable(GL_DEPTH_TEST);
        moremesh = new Mesh();
        return moremesh->LoadMesh(meshfile);
    }

    bool CRender::set_texture(const char* imgfile)
    {
        DELETE_PTR(_texture)
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        _gl_shardes->gluniform_sampler_1i(0);
        _texture = new Texture(GL_TEXTURE_2D, imgfile);
        if (!_texture->load_image())
        {
            return false;
        }
        return true;
    }
}
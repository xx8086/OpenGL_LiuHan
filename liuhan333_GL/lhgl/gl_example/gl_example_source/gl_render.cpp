#include "gl_render.h"
#include "lhgl_vertex_struct.h"
#include "base_config.h"


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

    bool CRender::init()
    { 
        return false; 
    }

    void CRender::render_scene_texture()
    {
        glClear(GL_COLOR_BUFFER_BIT  |  GL_DEPTH_BUFFER_BIT);
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
        if (_mesh)
        {
            _mesh->Render();
        }

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
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

    void CRender::set_shardes(const char* vs, const char* fs)
    {
        DELETE_PTR(_gl_shardes);
        _gl_shardes = new lh_gl::CShardes;
        _gl_shardes->glsharde_init(vs, fs);
    }

    bool CRender::set_mesh(const char* meshfile)
    {
        DELETE_PTR(_mesh)
        glEnable(GL_DEPTH_TEST);
        _mesh = new Mesh();
        return _mesh->LoadMesh(meshfile);// ("..\\res\\Content\\phoenix_ugv.md2");
    }

    bool CRender::set_texture(const char* imgfile)
    {
        DELETE_PTR(_texture)
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        _gl_shardes->gluniform_sampler_1i(0);
        _texture = new Texture(GL_TEXTURE_2D, imgfile);// "..\\res\\Content\\timg.jpg");
        if (!_texture->load_image())
        {
            return false;
        }
        return true;
    }
    
}
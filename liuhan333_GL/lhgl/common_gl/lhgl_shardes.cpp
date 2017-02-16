#include "lhgl_shardes.h"
#include "glm.hpp"
#include "lhgl_pipeline.h"
#include "glut.h"
#include "lhgl_key_trans.h"
#include "base_config.h"

namespace lh_gl_sharde {
    using namespace lh_gl;

    struct VertexText
    {
        Vector3f m_pos;
        Vector2f m_tex;

        VertexText() {}

        VertexText(Vector3f pos, Vector2f tex)
        {
            m_pos = pos;
            m_tex = tex;
        }
    };

    CShardes::CShardes()
    {
        init();
    }

    CShardes::CShardes(const char* vs, const char* fs):
        CLHShardes(vs, fs)
    {
        init();
    }

    CShardes::~CShardes()
    {
    }

    void CShardes::init()
    {
        init_camera();
        init_light();
    }

    void CShardes::release()
    {
        release_camera();
        release_texture();
    }
  
    bool CShardes::init_texture()
    {
        release_texture();

        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        glUniform1i(sampler_location, 0);
        texture = new Texture(GL_TEXTURE_2D, "..\\res\\Content\\timg.jpg");
        if (!texture->load_image()) 
        {
            return false;
        }
        return true;
    }

    void CShardes::release_texture()
    {
        DELETE_PTR(texture)
    }

    void CShardes::init_light()
    {
        directionallight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        directionallight.AmbientIntensity = 0.5f;
    }

    void CShardes::init_camera()
    {
        release_camera();
        game_camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, 
            Vector3f(0.0f, 0.0f, -5.0f), //pos
            Vector3f(0.45f, 0.0f, 2.0f), //target
            Vector3f(0.0f, 1.0f, 0.0f)); //up
        
    }

    void CShardes::release_camera()
    {
        DELETE_PTR(game_camera)
    }

    bool CShardes::onmouse(unsigned int mark, unsigned int x, unsigned int y)
    {
        bool rt = false;
        if(lh_mouse_move(mark))
        {
            rt = game_camera->om_mouse((int)x, (int)y);
        }
        return rt;
    }

    bool CShardes::specialkeyboard(bool bchar, unsigned int uchar, unsigned int utype)
    {
        LHGL_KEY key = lh_to_glkey(bchar, uchar);
        game_camera->on_keyboard(key);
        directionallight.on_keyboard(key);
        return true;
    }

    void CShardes::render_bypipe()
    {
        fscale += 0.1f;
        Pipeline p;
        p.Rotate(0.0f, fscale, 0.0f);
        p.WorldPos(0.0f, 0.0f, -1.0f);
        p.SetPerspectiveProj(pers_projInfo);// 设置投影变换的参数
        p.SetCamera(*game_camera);

        glUniformMatrix4fv(world_location, 1, GL_TRUE, (const GLfloat*)p.GetWVPTrans());// GetWorldTrans
        setdirectionallight();
    }

    void CShardes::render_triangle()
    {
        fscale += 0.01f;
        glUniform1f(scale_location, sinf(fscale));
    }

    void CShardes::render_rotate()
    {
        fscale += 0.01f;
        float world[16] = {
        cosf(fscale),    0.0f,   -sinf(fscale),       0.0f,
        0.0f,           1.0f,           0.0f,       0.0f,
        sinf(fscale),    0.0f,    cosf(fscale),       0.0f,
        0.0f,           0.0f,           0.0f,       1.0f};

        glUniformMatrix4fv(world_location, 1, GL_TRUE, world);
    }

    void CShardes::render_scale()
    {
        fscale += 0.01f;
        float world[16] = {
            sinf(fscale),   0.0f,           0.0f,           0.0f,
            0.0f,           sinf(fscale),   0.0f,           0.0f,
            0.0f,           0.0f,           sinf(fscale),   0.0f,
            0.0f,           0.0f,           0.0f,           1.0f };

        glUniformMatrix4fv(world_location, 1, GL_TRUE, world);
    }

    void CShardes::render_translation()
    {
        fscale += 0.01f;
        float world[16] = {
            1.0f, 0.0f, 0.0f, sinf(fscale),
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f };
        
        glUniformMatrix4fv(world_location, 1, GL_TRUE, world);
    }

    void CShardes::render_scene_texture()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        render_bypipe();
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexText), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexText), (const GLvoid*)12);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        texture->bind_image(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
    void CShardes::render_scene()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        //render_triangle();
        //render_translation();
        //render_rotate();
        //render_scale();
        render_bypipe();

        glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        //glutSwapBuffers();
    }

    bool CShardes::glsharde_init()
    {
        assert(CLHShardes::glsharde_init());
        set_vs_filename("..\\shardes\\shader.vs");
        set_fs_filename("..\\shardes\\shader.fs");
        
        create_vertex_texture();
        //create_vertex_buffer();
        create_index_buffer();
        init_projection();
        do_sharde();
        init_texture();
        return true;
    }


    void CShardes::create_index_buffer()
    {
        // 四个三角形面的顶点索引集
        unsigned int indices[] = { 
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2 };
        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }


    void CShardes::create_vertex_texture()
    {
        VertexText Vertices[4] = { 
            VertexText(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
            VertexText(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
            VertexText(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
            VertexText(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    }

    void CShardes::create_vertex_buffer()
    {
        float vertices[12] = {
            -1.0f, -1.0f, 0.5773f,
            0.0f, -1.0f, -1.15475f,
            1.0f, -1.0f, 0.5773f,
            0.0f, 1.0f, 0.0f };

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*12, vertices, GL_STATIC_DRAW);
    }

    bool CShardes::do_sharde()
    {
        assert(compile_shaders(shader_program));
        get_uniformlocation(shader_program, world_location, "gworld");
        get_uniformlocation(shader_program, sampler_location, "gsampler");
        get_uniformlocation(shader_program, dirlight_colorlocation, "gDirectionalLight.Color");
        get_uniformlocation(shader_program, dirlight_ambientintensitylocation, "gDirectionalLight.AmbientIntensity");

        return true;
    }

    void CShardes::init_projection()
    {
        pers_projInfo.FOV = 60.0f;
        pers_projInfo.Height = WINDOW_HEIGHT;
        pers_projInfo.Width = WINDOW_WIDTH;
        pers_projInfo.zNear = 1.0f;
        pers_projInfo.zFar = 100.0f;
    }

    void CShardes::setdirectionallight()
    {
        glUniform3f(dirlight_colorlocation, directionallight.Color.x, directionallight.Color.y, directionallight.Color.z);
        glUniform1f(dirlight_ambientintensitylocation, directionallight.AmbientIntensity);
    }
}
#include "lhgl_shardes.h"
#include "glm.hpp"
#include "lhgl_pipeline.h"
#include "glut.h"
#include "lhgl_key_trans.h"

namespace lh_gl_sharde {
    using namespace lh_gl;

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
    }

    void CShardes::release()
    {
        release_camera();
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
        if (game_camera != nullptr)
        {
            delete game_camera;
            game_camera = nullptr;
        }
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
        return game_camera->on_keyboard(lh_to_glkey(bchar, uchar));
    }

    void CShardes::render_bypipe()
    {
        fscale += 0.01f;
        Pipeline p;
        p.Rotate(0.0f, fscale, 0.0f);
        p.WorldPos(0.0f, 0.0f, -1.0f);
        p.SetPerspectiveProj(pers_projInfo);// 设置投影变换的参数
        p.SetCamera(*game_camera);

        glUniformMatrix4fv(world_location, 1, GL_TRUE, (const GLfloat*)p.GetWVPTrans());// GetWorldTrans
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
        create_vertex_buffer();
        create_index_buffer();
        init_projection();
        return do_sharde();
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
        //get_uniformlocation(shader_program, scale_location, "gScale");
        get_uniformlocation(shader_program, world_location, "gworld");
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
}
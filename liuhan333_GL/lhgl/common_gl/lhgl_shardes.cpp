﻿#include "lhgl_shardes.h"
#include "glm.hpp"

namespace lh_gl_sharde {
    CShardes::CShardes()
    {
    }

    CShardes::CShardes(const char* vs, const char* fs):
        CLHShardes(vs, fs)
    {}

    CShardes::~CShardes()
    {
    }
  
    void CShardes::render_triangle()
    {
        static float fscale = 0.0f;
        fscale += 0.01f;
        glUniform1f(scale_location, sinf(fscale));
    }

    void CShardes::render_rotate()
    {
        static float Scale = 0.0f;
        Scale += 0.01f;

        // 旋转变换矩阵
        float world[16] = {
        cosf(Scale),    -sinf(Scale),   0.0f,       0.0f,
        sinf(Scale),    cosf(Scale),    0.0f,       0.0f,
        0.0f,           0.0f,           1.0f,       0.0f,
        0.0f,           0.0f,           0.0f,       1.0f};

        glUniformMatrix4fv(world_location, 1, GL_TRUE, world);
    }

    void CShardes::render_scale()
    {
        static float fscale = 0.0f;
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
        static float fscale = 0.0f;
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

        render_triangle();
        //render_translation();
        //render_rotate();
        //render_scale();

        glEnableVertexAttribArray(0);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        //glutSwapBuffers();
    }

    bool CShardes::glsharde_init()
    {
        assert(CLHShardes::glsharde_init());
        set_vs_filename("..\\shardes\\shader.vs");
        set_fs_filename("..\\shardes\\shader.fs");
        create_vertex_buffer();
        return do_sharde();
    }

    void CShardes::create_vertex_buffer()
    {
        float vertices[9] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f };

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, vertices, GL_STATIC_DRAW);
    }

    bool CShardes::do_sharde()
    {
        assert(compile_shaders(shader_program));
        //get_uniformlocation(shader_program, scale_location, "gScale");
        get_uniformlocation(shader_program, world_location, "gworld");
        return true;
    }
}
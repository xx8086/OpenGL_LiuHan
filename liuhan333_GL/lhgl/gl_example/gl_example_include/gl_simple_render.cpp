#include "gl_simple_render.h"
#include "GL\glew.h"

namespace lh_gl {

    CGlSample::CGlSample()
    {}
    CGlSample::~CGlSample()
    {}

    void CGlSample::do_render()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        static float sf = 0.0;
        sf += 0.01;
        float sca = 0.3;// sinf(sf);
        float v[16] = {
            sca,    0.0f,   0.0,    -0.7f,
            0.0f,   sca,    0.0f,    0.0f,
            0.0,     0.0f,  sca,    0.0f,
            0.0f,   0.0f,   0.0f,    1.0
        };
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, v);


        glBindBuffer(GL_ARRAY_BUFFER, bao);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vertex_postions));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


        float v2[16] = {
            sca,    0.0f,   0.0,    -0.5f,
            0.0f,   sca,    0.0f,    0.0f,
            0.0,     0.0f,  sca,    0.0f,
            0.0f,   0.0f,   0.0f,    1.0
        };
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, v2);
        glBindVertexArray(vao);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(vertex_postions));

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glFlush();
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        //glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0, 1);
        ////glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

    }

    bool CGlSample::init()
    {
        glewInit();

        glGenVertexArrays(1, &vao);//顶点数组对象
        glBindVertexArray(vao);

        glGenBuffers(1, &bao);//顶点缓存对象
        glBindBuffer(GL_ARRAY_BUFFER, bao);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_postions)+ sizeof(vertex_colors), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_postions), vertex_postions);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_postions), sizeof(vertex_colors), vertex_colors);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);

        init_shardes();

        return true;
    }

    void CGlSample::init_shardes()
    {
        _gl_shardes = new lh_gl::CShardes;
        _gl_shardes->glsharde_init();
        _gl_shardes->uniformlocation();
    }

    bool CGlSample::onmouse(unsigned int mark, unsigned int x, unsigned int y)
    {
        return false;
    }
    bool CGlSample::specialkeyboard(bool, unsigned int, unsigned int)
    {
        return false;
    }
}
#include "gl_shardes.h"
#include "lhgl_util.h"
#include "lhgl_vertex_struct.h"
#include <assert.h>

namespace lh_gl {
    CShardes::CShardes()
    {}

    CShardes::~CShardes()
    {}

    bool CShardes::glsharde_init(const char* vs, const char* fs)
    {
        assert(CLHShardes::glsharde_init(vs, fs));
        return true;
    }

    bool CShardes::uniformlocation()
    {
        assert(compile_shaders(_shader_program));
        uniformlocation_base();
        uniform_direction_lights_location();
        uniform_point_lights_location();
        uniform_spot_lights_location();
        return true;
    }

    bool CShardes::gl_enable()
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        return true;
    }
    
    bool CShardes::gl_drawelements(GLuint vbo, GLuint ibo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexText), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexText), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexText), (const GLvoid*)20);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        return true;
    }

    bool CShardes::gl_disable()
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        return true;
    }
}
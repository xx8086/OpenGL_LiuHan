#ifndef GL_INCLUDE_GL_VERTEX_INTERFACE_H
#define	GL_INCLUDE_GL_VERTEX_INTERFACE_H

#include "gl_vertex.h"

namespace lh_gl {
    class CGlVertexInterface : protected CGvertex
    {
    public:
        CGlVertexInterface();
        virtual ~CGlVertexInterface();
    public:
        bool get_usetex()const;
        GLuint get_ibo() const;
        GLuint get_vbo() const;
    public:
        bool create_vertex();
    };
}
#endif

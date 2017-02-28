#include "gl_vertex_interface.h"

namespace lh_gl {

    CGlVertexInterface::CGlVertexInterface()
    {}

    CGlVertexInterface::~CGlVertexInterface()
    {}

    bool CGlVertexInterface::create_vertex()
    {
        create_indices_buffer();
        create_texture();
        return true;
    }

    bool CGlVertexInterface::get_usetex()const
    {
        return (true == _busetex);
    }

    GLuint CGlVertexInterface::get_ibo() const
    {
        return _ibo;
    }

    GLuint CGlVertexInterface::get_vbo() const
    {
        return _vbo;
    }

}
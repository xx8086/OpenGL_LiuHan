#ifndef GL_INCLUDE_GL_VERTEX_H
#define	GL_INCLUDE_GL_VERTEX_H
#include "GL\glew.h"
#include "lhgl_vertex_struct.h"

namespace lh_gl {

    class CGvertex
    {
    public:
        CGvertex();
        virtual ~CGvertex();

    public:
        bool set_indices(int, unsigned int*);
        bool set_vertices(int, VertexText*);
    protected:
        void release();
        void create_indices_buffer();
        void create_texture();
        void calc_normals(const unsigned int* pIndices, unsigned int IndexCount,
            VertexText* pVertices, unsigned int VertexCount);
    protected:
        bool _busetex = false;
        GLuint _ibo = 0;
        GLuint _vbo = 0;
    private:
        unsigned int* _indices = nullptr;
        int _indices_nums = 0;
        VertexText* _vertices = nullptr;
        int _vertices_nums = 0;
    };
}

#endif

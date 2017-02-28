#ifndef GL_INCLUDE_GL_VERTEX_H
#define	GL_INCLUDE_GL_VERTEX_H
#include "GL\glew.h"
#include "gl_vertex_struct.h"

namespace lh_gl {

    class CGvertex
    {
    public:
        CGvertex();
        virtual ~CGvertex();

    protected:
        void create_vertex_buffer();
        void create_indices_buffer();
        void create_texture();
        void calc_normals(const unsigned int* pIndices, unsigned int IndexCount,
            VertexText* pVertices, unsigned int VertexCount);
    protected:
        bool _busetex = false;
        GLuint _ibo = 0;
        GLuint _vbo = 0;
    private:
        unsigned int _indices[12] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            1, 2, 0 };
        VertexText _vertices[4] = {
            VertexText(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
            VertexText(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
            VertexText(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
            VertexText(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)) };
    };
}

#endif

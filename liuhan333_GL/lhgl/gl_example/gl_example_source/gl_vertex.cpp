#include "gl_vertex.h"
#include "lhgl_vertex_struct.h"

namespace lh_gl {

    CGvertex::CGvertex()
    {}

    CGvertex::~CGvertex()
    {}

    void CGvertex::create_vertex_buffer()
    {
        float vertices[12] = {
            -1.0f, -1.0f, 0.5773f,
            0.0f, -1.0f, -1.15475f,
            1.0f, -1.0f, 0.5773f,
            0.0f, 1.0f, 0.0f };

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertices, GL_STATIC_DRAW);
        _busetex = false;
    }

    void CGvertex::create_indices_buffer()
    {
        glGenBuffers(1, &_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);
    }

    void CGvertex::create_texture()
    {
        calc_normals(_indices, ARRAY_SIZE_IN_ELEMENTS(_indices), _vertices, ARRAY_SIZE_IN_ELEMENTS(_vertices));

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

        _busetex = true;
    }

    void CGvertex::calc_normals(const unsigned int* pIndices, unsigned int IndicesCount,
        VertexText* pVertices, unsigned int VertexCount)
    {
        for (unsigned int i = 0; i < IndicesCount; i += 3) {
            unsigned int Index0 = pIndices[i];
            unsigned int Index1 = pIndices[i + 1];
            unsigned int Index2 = pIndices[i + 2];
            Vector3f v1 = pVertices[Index1].m_pos - pVertices[Index0].m_pos;
            Vector3f v2 = pVertices[Index2].m_pos - pVertices[Index0].m_pos;
            Vector3f Normal = v1.Cross(v2);//计算三角形012的法线。
            Normal.Normalize();

            pVertices[Index0].m_normal += Normal;
            pVertices[Index1].m_normal += Normal;
            pVertices[Index2].m_normal += Normal;
        }

        for (unsigned int i = 0; i < VertexCount; i++) {
            pVertices[i].m_normal.Normalize();
        }
    }
}
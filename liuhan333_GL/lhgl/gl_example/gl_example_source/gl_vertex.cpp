#include "gl_vertex.h"
#include "lhgl_vertex_struct.h"

namespace lh_gl {

    CGvertex::CGvertex()
    {}

    CGvertex::~CGvertex()
    {
        release();
    }

    void CGvertex::release()
    {
        if (nullptr != _indices)
        {
            delete[] _indices;
            _indices = nullptr;
        }

        if (nullptr != _vertices)
        {
            delete[] _vertices;
            _vertices = nullptr;
        }
    }

    bool CGvertex::set_indices(int nums, unsigned int* ind)
    {
        if (nums < 1 || nullptr == ind)
        {
            return false;
        }

        _indices = new unsigned int[nums];
        memcpy(_indices, ind, nums * sizeof(unsigned int));
        _indices_nums = nums;
    }
    bool CGvertex::set_vertices(int nums, VertexText* vert)
    {
        if (nums < 1 || nullptr == vert)
        {
            return false;
        }

        _vertices = new VertexText[nums];
        memcpy(_vertices, vert, nums * sizeof(VertexText));
        _vertices_nums = nums;
    }

    void CGvertex::create_indices_buffer()
    {
        glGenBuffers(1, &_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            _indices_nums * sizeof(unsigned int), 
            _indices, GL_STATIC_DRAW);
    }

    void CGvertex::create_texture()
    {
        calc_normals(_indices, _indices_nums, _vertices, _vertices_nums);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices_nums * sizeof(VertexText),
            _vertices, GL_STATIC_DRAW);

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
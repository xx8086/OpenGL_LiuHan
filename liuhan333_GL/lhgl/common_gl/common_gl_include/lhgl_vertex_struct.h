#ifndef GL_VXERTEX_STRUCT_H
#define	GL_VXERTEX_STRUCT_H

#include "lhgl_math.h"

namespace lh_gl {
    struct VertexText
    {
        Vector3f m_pos;
        Vector2f m_tex;
        Vector3f m_normal;

        VertexText() {}
        VertexText(Vector3f pos, Vector2f tex)
        {
            m_pos = pos;
            m_tex = tex;
            m_normal = Vector3f(0.0f, 0.0f, 0.0f);
        }
    };

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
}

#endif
#include "gl_example_model_mx.h"

namespace lh_gl {

    void CRanderExModelMX::do_render()
    {
        CRender::do_render();
    }
    bool CRanderExModelMX::init()
    {
        set_shardes("..\\shardes\\shader.vs", "..\\shardes\\shader.fs");
        set_main_camera(Vector3f(0.0f, 0.0f, -7.0f),
            Vector3f(0.0f, 0.0f, 1.0f),
            Vector3f(0.0f, 1.0f, 0.0f));
        set_projection(60.0f, 1.0f, 100.0f);
        set_main_directionlight(Vector3f(1.0f, 1.0f, 1.0f),
            Vector3f(1.0f, 0.0f, 0.0f),
            0.01f,
            0.75f);

        set_mesh("..\\res\\Content\\phoenix_ugv.md2");
        return true;
    }
}

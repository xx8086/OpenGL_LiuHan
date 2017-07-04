#include "gl_example_pyramid.h"
#include "lhgl_pipeline.h"
#include "base_config.h"

namespace lh_gl {

    CRanderExPyramid::~CRanderExPyramid()
	{}

    void CRanderExPyramid::render_bypipe()
    {
        _fscale += 0.1f;
        Pipeline p;
        p.Scale(0.3f);
        p.Rotate(_fscale, 0.0f, 0.0f);
        p.WorldPos(0.0f, 0.0f, -5.0f);
        p.SetPerspectiveProj(_pers_projInfo);// 设置投影变换的参数
        p.SetCamera(*_game_camera);
        _gl_shardes->gluniform_world_matrix_4fv(1, GL_TRUE, (const GLfloat*)p.GetWorldTrans().m);
        _gl_shardes->gluniform_wvp_matrix_4fv(1, GL_TRUE, (const GLfloat*)p.GetWVPTrans().m);
        _gl_shardes->gluniform_specular_reflection(_game_camera->GetPos(), 1.0, 10);

        set_directional_light();
        set_point_light();
        set_spot_light();
    }

    void CRanderExPyramid::do_render()
    {
        CRender::do_render();
    }

    bool CRanderExPyramid::init()
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
        set_vertex(12, _indices, 4, _vertices);
        set_texture("..\\res\\Content\\timg.jpg");
       // set_mesh("..\\res\\Content\\phoenix_ugv.md2");
        return true;
    }
    void CRanderExPyramid::set_point_light()
    {
        PointLight pl[2];
        pl[0].DiffuseIntensity = 0.5f;
        pl[0].Color = Vector3f(1.0f, 0.5f, 0.0f);
        pl[0].Position = Vector3f(130.0f, 100.0f, 300 * FieldDepth * (cosf(_fscale) + 1.0f) / 2.0f);
        pl[0].Attenuation.Linear = 10.0f;
        pl[0].Attenuation.Exp = 2.0f;
        pl[1].DiffuseIntensity = 0.5f;
        pl[1].Color = Vector3f(0.0f, 0.5f, 1.0f);
        pl[1].Position = Vector3f(7.0f, 1.0f, FieldDepth * (sinf(_fscale) + 1.0f) / 2.0f);
        pl[1].Attenuation.Linear = 0.1f;
        _gl_shardes->gluniform_setpointlights(2, pl);
	}

    void CRanderExPyramid::set_spot_light()
    {
        SpotLight sl[2];
        sl[0].DiffuseIntensity = 0.9f;
        sl[0].Color = Vector3f(0.0f, 1.0f, 1.0f);
        sl[0].Position = _game_camera->GetPos();
        sl[0].Direction = _game_camera->GetTarget();
        sl[0].Attenuation.Linear = 0.1f;
        sl[0].Cutoff = 10.0f;

        sl[1].DiffuseIntensity = 0.9f;
        sl[1].Color = Vector3f(1.0f, 1.0f, 1.0f);
        sl[1].Position = Vector3f(5.0f, 3.0f, 10.0f);
        sl[1].Direction = Vector3f(0.0f, -1.0f, 0.0f);
        sl[1].Attenuation.Linear = 0.1f;
        sl[1].Cutoff = 20.0f;
        _gl_shardes->gluniform_setspotlights(2, sl);
	}

    void CRanderExPyramid::set_directional_light()
    {
        _gl_shardes->gluniform_directionlight(_directionallight);
    }

    void CRanderExPyramid::set_shardes(const char* vs, const char* fs)
    {
        DELETE_PTR(_gl_shardes);
        _gl_shardes = new lh_gl::CShardes;
        _gl_shardes->glsharde_init(vs, fs);
        _gl_shardes->uniformlocation();
    }
}

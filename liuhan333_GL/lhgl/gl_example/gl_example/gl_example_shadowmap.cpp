#include "gl_example_shadowmap.h"
#include "gl_shadowmap.h"
#include "lhgl_pipeline.h"

namespace lh_gl {
    CRanderShadowMap::CRanderShadowMap()
    {
    }


    CRanderShadowMap::~CRanderShadowMap()
    {
    }

    void CRanderShadowMap::do_render()
    {
        CRender::do_render();
    }

    void CRanderShadowMap::set_spot_light()
    {
        _spot_light.AmbientIntensity = 0.0f;
        _spot_light.DiffuseIntensity = 0.9f;
        _spot_light.Color = Vector3f(1.0f, 1.0f, 1.0f);
        _spot_light.Position = Vector3f(-20.0, 20.0, 5.0f);
        _spot_light.Direction = Vector3f(1.0f, -1.0f, 0.0f);
        _spot_light.Attenuation.Linear = 0.01f;
        _spot_light.Cutoff = 20.0f;

    }

    bool CRanderShadowMap::init()
    {
        set_shardes<lh_gl::CShadowMapFBO>("..\\shardes\\shadow_map.vs", 
            "..\\shardes\\shadow_map.fs");
        ((lh_gl::CShadowMapFBO*) _gl_shardes)->init(WINDOW_WIDTH, WINDOW_HEIGHT);
        set_main_camera(Vector3f(0.0f, 0.0f, 0.0f),
            Vector3f(0.0f, 0.0f, 1.0f),
            Vector3f(0.0f, 1.0f, 0.0f));
        set_projection(20.0f, 1.0f, 100.0f);
        set_spot_light();

        set_mesh(_mesh_quad, "..\\res\\Content\\quad.obj");
        set_mesh("..\\res\\Content\\phoenix_ugv.md2");
        return true;
    }

    void CRanderShadowMap::render_scene_texture()
    {
        render_bypipe();
    }

    void CRanderShadowMap::render_bypipe_framebuffer()
    {
        ((lh_gl::CShadowMapFBO*) _gl_shardes)->bindfoewriting();
        glClear(GL_DEPTH_BUFFER_BIT);

        Pipeline p;
        p.Scale(0.1f, 0.1f, 0.1f);
        p.Rotate(0.0f, _fscale, 0.0f);
        p.WorldPos(0.0f, 0.0f, 5.0f);
        p.SetCamera(_spot_light.Position, _spot_light.Direction, Vector3f(0.0f, 1.0f, 0.0f));
        //p.SetCamera(Vector3f(-10.0, 20.0, 5.0f), Vector3f(1.0f, -1.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
        p.SetPerspectiveProj(_pers_projInfo);
        ((lh_gl::CShadowMapFBO*) _gl_shardes)->se_wvp(p.GetWVPTrans());
        
        _gl_shardes->gl_enable();
        _mesh->Render();
        _gl_shardes->gl_disable();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void CRanderShadowMap::render_bypipe_frametexture()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ((lh_gl::CShadowMapFBO*) _gl_shardes)->set_textureunit(0);
        ((lh_gl::CShadowMapFBO*) _gl_shardes)->bindtexture(GL_TEXTURE0);

        Pipeline p;
        p.Scale(5.0f, 5.0f, 5.0f);
        p.WorldPos(0.0f, 0.0f, 10.0f);
        p.SetCamera(_game_camera->GetPos(), _game_camera->GetTarget(), _game_camera->GetUp());
        p.SetPerspectiveProj(_pers_projInfo);
        ((lh_gl::CShadowMapFBO*) _gl_shardes)->se_wvp(p.GetWVPTrans());

        _gl_shardes->gl_enable();
        _mesh_quad->Render();
        _gl_shardes->gl_disable();
    }
    void CRanderShadowMap::render_bypipe()
    {
        _fscale += 0.05f;
        render_bypipe_framebuffer();
        render_bypipe_frametexture();
    }

}
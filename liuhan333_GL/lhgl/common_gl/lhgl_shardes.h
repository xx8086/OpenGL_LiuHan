#ifndef LHGL_SHARDES_H
#define	LHGL_SHARDES_H
#include "lhsharde.h"
#include "GL\glew.h"
#include "lhgl_math.h"
#include "lhgl_camera.h"
#include "lhgl_image.h"
#include "lhgl_lights_common.h"

namespace lh_gl_sharde {

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

    class CShardes:
        private CLHShardes
    {
    public:
        CShardes(const char*, const char*);
        CShardes();
        virtual ~CShardes();
    public:
        bool glsharde_init();
        void create_index_buffer();
        void create_vertex_buffer();
        void create_vertex_texture();
        void render_scene();
        void render_scene_texture();
    public:
        bool onmouse(unsigned int mark, unsigned int x, unsigned int y);
        bool specialkeyboard(bool, unsigned int, unsigned int);
    private:
        void render_bypipe();
        void render_translation();
        void render_rotate();
        void render_scale();
        void render_triangle();
        bool do_sharde();
        void setdirectionallight();

    private:
        void init_projection();
        bool init_texture();
        void release_texture();
        void init_camera();
        void init_light();
        void release_camera();
    private:
        void init();
        void release();
    private:
        float fscale = 0.0f;
        GLuint ibo;
        GLuint vbo;
        GLuint shader_program;
        GLuint scale_location;
        GLuint world_location;
        GLuint sampler_location;
        GLuint dirlight_colorlocation;
        GLuint dirlight_ambientintensitylocation;


        lh_gl::PersProjInfo pers_projInfo;
        lh_gl::DirectionalLight directionallight;
        lh_gl::Camera* game_camera = nullptr;
        lh_gl::Texture* texture = nullptr;
    };
}
#endif
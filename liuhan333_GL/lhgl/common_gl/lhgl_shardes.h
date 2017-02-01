#ifndef LHGL_SHARDES_H
#define	LHGL_SHARDES_H
#include "lhsharde.h"
#include "GL\glew.h"
#include "lhgl_math.h"
#include "lhgl_camera.h"

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
        void render_scene();
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

    private:
        void init_projection();
        void init_camera();
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
        lh_gl::PersProjInfo pers_projInfo;
        lh_gl::Camera* game_camera = nullptr;
    };
}
#endif
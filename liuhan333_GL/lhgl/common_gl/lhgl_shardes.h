#ifndef LHGL_SHARDES_H
#define	LHGL_SHARDES_H
#include "lhsharde.h"
#include "GL\glew.h"

namespace lh_gl_sharde {
    class CShardes:
        private CLHShardes
    {
    public:
        CShardes(const char*, const char*);
        CShardes();
        virtual ~CShardes();
    public:
        bool glsharde_init();
        void create_vertex_buffer();
        void render_scene();
        
    private:
        void render_translation();
        void render_rotate();
        void render_scale();
        void render_triangle();
        bool do_sharde();
    private:
        GLuint vbo;
        GLuint shader_program;
        GLuint scale_location;
        GLuint world_location;
    };
}
#endif
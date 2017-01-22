#ifndef LHGL_SHARDES_H
#define	LHGL_SHARDES_H

#include <GL/glew.h>
#include <string>

namespace lh_gl {
    class CShardes
    {
    public:
        CShardes(const char*, const char*);
        CShardes();
        virtual ~CShardes();
    public:
        bool compile_shaders();
        bool init();
        void create_vertex_buffer();
        void render_scene();
        void set_vs_filename(const char*);
        void set_fs_filename(const char*);
    private:
        
        bool add_shader(GLuint, const char*, GLenum);
    private:
        std::string str_vs_filename;
        std::string str_fs_filename;
    private:
        GLuint vbo;
        GLuint shader_program;
        GLuint scale_location;
    };
}
#endif
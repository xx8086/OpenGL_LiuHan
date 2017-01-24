#ifndef LH_SHARDE_H
#define LH_SHARDE_H

#include <GL/glew.h>
#include <string>

namespace lh_gl_sharde {
    class CLHShardes
    {
    public:
        CLHShardes(const char*, const char*);
        CLHShardes();
        virtual ~CLHShardes();
    protected:
        virtual bool glsharde_init();
        bool get_uniformlocation(const GLuint shader_program, GLuint& getlication, const char* lication);
        bool compile_shaders(GLuint&);
        void set_vs_filename(const char*);
        void set_fs_filename(const char*);
    private:
        bool add_shader(GLuint, const char*, GLenum);
    private:
        std::string str_vs_filename;
        std::string str_fs_filename;
    
    };
}

#endif
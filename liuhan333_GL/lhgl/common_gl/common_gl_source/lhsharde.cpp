#include "lhsharde.h"
#include <stdio.h>
#include <string.h>
#include "base_config.h"
#include "lhgl_util.h"
#include "glut.h"
#include "glm.hpp"

namespace lh_gl {
    CLHShardes::CLHShardes(const char* vs, const char* fs) :
        str_vs_filename(vs), str_fs_filename(fs)
    {}

    CLHShardes::CLHShardes()
    {}

    CLHShardes::~CLHShardes()
    {}

    bool CLHShardes::compile_shaders(GLuint& shader_program)
    {
        shader_program = glCreateProgram();
        if (shader_program == 0)
        {
            LHGL_ERROR("Error creating shader program\n");
            return false;
        }

        std::string vs, fs;

        FALSE_RT(read_file(str_vs_filename.c_str(), vs), false)
        FALSE_RT(read_file(str_fs_filename.c_str(), fs), false)

        FALSE_RT(add_shader(shader_program, vs.c_str(), GL_VERTEX_SHADER), false)
        FALSE_RT(add_shader(shader_program, fs.c_str(), GL_FRAGMENT_SHADER), false)

        GLint success = 0;
        GLchar error_log[MSG_BUFFER_LEN] = { 0 };

        glLinkProgram(shader_program);
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (success == 0)
        {
            glGetProgramInfoLog(shader_program, sizeof(error_log), NULL, error_log);
            LHGL_ERROR("Error linking shader program: '%s'\n", error_log);
            return false;
        }

        glValidateProgram(shader_program);
        glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_program, sizeof(error_log), NULL, error_log);
            LHGL_ERROR("Invalid shader program: '%s'\n", error_log);
            return false;
        }

        glUseProgram(shader_program);
        return true;
    }

    bool CLHShardes::glsharde_init()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
        GLenum res = glewInit();
        if (res != GLEW_OK)
        {
            LHGL_ERROR("Error: '%s'\n", glewGetErrorString(res));
            return false;
        }

        LHGL_MSG("GL_VERSION", (char*)glGetString(GL_VERSION));
        return true;
    }

    void CLHShardes::set_vs_filename(const char* pvs)
    {
        if (pvs)
        {
            str_vs_filename = pvs;
        }
    }

    void CLHShardes::set_fs_filename(const char* pfs)
    {
        if (pfs)
        {
            str_fs_filename = pfs;
        }
    }

    bool CLHShardes::add_shader(GLuint shader_program, const char* shader_text, GLenum shader_type)
    {
        GLuint shader_obj = glCreateShader(shader_type);
        if (shader_obj == 0)
        {
            LHGL_ERROR("Error creating shader type %d\n", shader_type);
            return false;
        }

        const GLchar* p[1];
        p[0] = shader_text;
        GLint Lengths[1];
        Lengths[0] = strlen(shader_text);
        glShaderSource(shader_obj, 1, p, Lengths);
        glCompileShader(shader_obj);
        GLint success;
        glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar info_log[MSG_BUFFER_LEN];
            glGetShaderInfoLog(shader_obj, MSG_BUFFER_LEN, NULL, info_log);
            LHGL_ERROR("Error compiling shader type %d: '%s'\n", shader_type, info_log);
            return false;
        }

        glAttachShader(shader_program, shader_obj);
        return true;
    }

    bool CLHShardes::get_uniformlocation(const GLuint shader_program, GLuint& getlication, const char* lication)
    {
        getlication = glGetUniformLocation(shader_program, lication);
        assert(getlication != 0xFFFFFFFF);
        return true;
    }

    GLuint CLHShardes::get_uniformlocation(const GLuint shader_program, const char* lication)
    {
        GLuint getlication = glGetUniformLocation(shader_program, lication);
        assert(getlication != 0xFFFFFFFF);
        return getlication;
    }
}

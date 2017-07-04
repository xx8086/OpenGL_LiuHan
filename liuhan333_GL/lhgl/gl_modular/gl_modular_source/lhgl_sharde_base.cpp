#include "lhgl_sharde_base.h"
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

    bool CLHShardes::glsharde_init(const char* cs_vs, const char* cs_fs)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
        GLenum res = glewInit();
        if (res != GLEW_OK)
        {
            LHGL_ERROR("Error: '%s'\n", glewGetErrorString(res));
            return false;
        }

        LHGL_MSG("GL_VERSION", (char*)glGetString(GL_VERSION));
        set_vs_filename(cs_vs);
        set_fs_filename(cs_fs);
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

    bool CLHShardes::uniformlocation_base()
    {
        _world_location = get_uniformlocation(_shader_program, "gworld");
        _wvp_location = get_uniformlocation(_shader_program, "gwvp");
        _sampler_location = get_uniformlocation(_shader_program, "gsampler");
        _eye_worldpos = get_uniformlocation(_shader_program, "gEyeWorldPos");
        _mat_specular_intensity = get_uniformlocation(_shader_program, "gMatSpecularIntensity");
        _specular_power = get_uniformlocation(_shader_program, "gSpecularPower");
        return true;
    }

    bool CLHShardes::uniform_direction_lights_location()
    {
        _direction_light_location._dirlight_colorlocation = get_uniformlocation(_shader_program, "gDirectionalLight.Base.Color");
        _direction_light_location._dirlight_ambientintensitylocation = get_uniformlocation(_shader_program, "gDirectionalLight.Base.AmbientIntensity");
        _direction_light_location._dirlight_directionlocation = get_uniformlocation(_shader_program, "gDirectionalLight.Direction");
        _direction_light_location._dirlight_diffuseintensitylocation = get_uniformlocation(_shader_program, "gDirectionalLight.Base.DiffuseIntensity");
        return true;
    }

    bool CLHShardes::uniform_spot_lights_location()
    {
        _numspot_lights_location = get_uniformlocation(_shader_program, "gNumSpotLights");
        int iszie = ARRAY_SIZE_IN_ELEMENTS(_spotLightsLocation);
        for (unsigned int i = 0; i < iszie; i++) {
            char Name[128];
            memset(Name, 0, sizeof(Name));
            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.Color", i);
            _spotLightsLocation[i].Color = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.AmbientIntensity", i);
            _spotLightsLocation[i].AmbientIntensity = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Position", i);
            _spotLightsLocation[i].Position = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
            _spotLightsLocation[i].Direction = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
            _spotLightsLocation[i].Cutoff = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.DiffuseIntensity", i);
            _spotLightsLocation[i].DiffuseIntensity = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Constant", i);
            _spotLightsLocation[i].Atten.Constant = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Linear", i);
            _spotLightsLocation[i].Atten.Linear = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Exp", i);
            _spotLightsLocation[i].Atten.Exp = get_uniformlocation(_shader_program, Name);

            if (_spotLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
                _spotLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
                _spotLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
                _spotLightsLocation[i].Direction == INVALID_UNIFORM_LOCATION ||
                _spotLightsLocation[i].Cutoff == INVALID_UNIFORM_LOCATION ||
                _spotLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
                _spotLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
                _spotLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
                _spotLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
                return false;
            }
        }
        return true;
    }

    bool CLHShardes::uniform_point_lights_location()
    {
        _numpoint_lights_location = get_uniformlocation(_shader_program, "gNumPointLights");
        int iszie = ARRAY_SIZE_IN_ELEMENTS(_point_lights_location);
        for (unsigned int i = 0; i < iszie; i++)
        {
            char Name[128] = { 0 };
            SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
            _point_lights_location[i].Color = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
            _point_lights_location[i].AmbientIntensity = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
            _point_lights_location[i].Position = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
            _point_lights_location[i].DiffuseIntensity = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
            _point_lights_location[i].Atten.Constant = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
            _point_lights_location[i].Atten.Linear = get_uniformlocation(_shader_program, Name);

            SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
            _point_lights_location[i].Atten.Exp = get_uniformlocation(_shader_program, Name);

        }
        return true;
    }

    void CLHShardes::gluniform_setpointlights(unsigned int num_lights, const PointLight* plights)
    {
        glUniform1i(_numpoint_lights_location, num_lights);
        for (unsigned int i = 0; i < num_lights; i++) {
            glUniform3f(_point_lights_location[i].Color, plights[i].Color.x, plights[i].Color.y, plights[i].Color.z);
            glUniform1f(_point_lights_location[i].AmbientIntensity, plights[i].AmbientIntensity);
            glUniform1f(_point_lights_location[i].DiffuseIntensity, plights[i].DiffuseIntensity);
            glUniform3f(_point_lights_location[i].Position, plights[i].Position.x, plights[i].Position.y, plights[i].Position.z);
            glUniform1f(_point_lights_location[i].Atten.Constant, plights[i].Attenuation.Constant);
            glUniform1f(_point_lights_location[i].Atten.Linear, plights[i].Attenuation.Linear);
            glUniform1f(_point_lights_location[i].Atten.Exp, plights[i].Attenuation.Exp);
        }
    }

    void CLHShardes::gluniform_setspotlights(unsigned int NumLights, const SpotLight* pLights)
    {
        glUniform1i(_numspot_lights_location, NumLights);
        for (unsigned int i = 0; i < NumLights; i++)
        {
            glUniform3f(_spotLightsLocation[i].Color, pLights[i].Color.x, pLights[i].Color.y, pLights[i].Color.z);
            glUniform1f(_spotLightsLocation[i].AmbientIntensity, pLights[i].AmbientIntensity);
            glUniform1f(_spotLightsLocation[i].DiffuseIntensity, pLights[i].DiffuseIntensity);
            glUniform3f(_spotLightsLocation[i].Position, pLights[i].Position.x, pLights[i].Position.y, pLights[i].Position.z);
            Vector3f Direction = pLights[i].Direction;
            Direction.Normalize();
            glUniform3f(_spotLightsLocation[i].Direction, Direction.x, Direction.y, Direction.z);
            glUniform1f(_spotLightsLocation[i].Cutoff, cosf(ToRadian(pLights[i].Cutoff)));
            glUniform1f(_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
            glUniform1f(_spotLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
            glUniform1f(_spotLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
        }
    }

    void CLHShardes::gluniform_directionlight(const DirectionalLight& dl)
    {
        glUniform3f(_direction_light_location._dirlight_colorlocation, dl.Color.x, dl.Color.y, dl.Color.z);
        glUniform1f(_direction_light_location._dirlight_ambientintensitylocation, dl.AmbientIntensity);

        Vector3f direction = dl.Direction;
        direction.Normalize();
        glUniform3f(_direction_light_location._dirlight_directionlocation, direction.x, direction.y, direction.z);
        glUniform1f(_direction_light_location._dirlight_diffuseintensitylocation, dl.DiffuseIntensity);
    }

    void CLHShardes::gluniform_wvp_matrix_4fv(int count, GLboolean b, const GLfloat* world)
    {
        glUniformMatrix4fv(_wvp_location, count, b, world);
    }

    void CLHShardes::gluniform_world_matrix_4fv(int count, GLboolean b, const GLfloat* world)
    {
        glUniformMatrix4fv(_world_location, count, b, world);
    }

    void CLHShardes::gluniform_scale_1f(const float& fscale)
    {
        glUniform1f(_scale_location, fscale);
    }

    void CLHShardes::gluniform_sampler_1i(const unsigned int& sampler)
    {
        glUniform1i(_sampler_location, sampler);
    }

    void CLHShardes::gluniform_specular_reflection(const Vector3f& wpos, float intensity, float power)
    {
        glUniform3f(_eye_worldpos, wpos.x, wpos.y, wpos.z);
        glUniform1f(_mat_specular_intensity, intensity);
        glUniform1f(_specular_power, power);
    }

}

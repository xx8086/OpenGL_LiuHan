#include "gl_shardes.h"
#include <assert.h>

namespace lh_gl {
    CShardes::CShardes()
    {}

    CShardes::~CShardes()
    {}

    bool CShardes::glsharde_init()
    {
        assert(CLHShardes::glsharde_init());
        set_vs_filename("..\\shardes\\shader.vs");
        set_fs_filename("..\\shardes\\shader.fs");
        return true;
    }

    bool CShardes::uniformlocation()
    {
        assert(compile_shaders(_shader_program));
        //_scale_location = get_uniformlocation(_shader_program, "gScale");
        _world_location = get_uniformlocation(_shader_program, "gworld");
        _wvp_location = get_uniformlocation(_shader_program, "gwvp");
        _sampler_location = get_uniformlocation(_shader_program, "gsampler");
        _dirlight_colorlocation = get_uniformlocation(_shader_program, "gDirectionalLight.Color");
        _dirlight_ambientintensitylocation = get_uniformlocation(_shader_program, "gDirectionalLight.AmbientIntensity");
        _dirlight_directionlocation = get_uniformlocation(_shader_program, "gDirectionalLight.Direction");
        _dirlight_diffuseintensitylocation = get_uniformlocation(_shader_program, "gDirectionalLight.DiffuseIntensity");

        _eye_worldpos = get_uniformlocation(_shader_program, "gEyeWorldPos");
        _mat_specular_intensity = get_uniformlocation(_shader_program, "gMatSpecularIntensity");
        _specular_power = get_uniformlocation(_shader_program, "gSpecularPower");

        return true;
    }

    void CShardes::gluniform_wvp_matrix_4fv(int count, GLboolean b, const GLfloat* world)
    {
        glUniformMatrix4fv(_wvp_location, count, b, world);
    }

    void CShardes::gluniform_world_matrix_4fv(int count, GLboolean b, const GLfloat* world)
    {
        glUniformMatrix4fv(_world_location, count, b, world);
    }

    void CShardes::gluniform_scale_1f(const float& fscale)
    {
        glUniform1f(_scale_location, fscale);
    }

    void CShardes::gluniform_sampler_1i(const unsigned int& sampler)
    {
        glUniform1i(_sampler_location, 0);
    }

    void CShardes::gluniform_light(const DirectionalLight& dl)
    {
        glUniform3f(_dirlight_colorlocation, dl.Color.x, dl.Color.y, dl.Color.z);
        glUniform1f(_dirlight_ambientintensitylocation, dl.AmbientIntensity);

        Vector3f direction = dl.Direction;
        direction.Normalize();
        glUniform3f(_dirlight_directionlocation, direction.x, direction.y, direction.z);
        glUniform1f(_dirlight_diffuseintensitylocation, dl.DiffuseIntensity);

        
    }

    void CShardes::gluniform_specular_reflection(const Vector3f& wpos, float intensity, float power)
    {
        glUniform3f(_eye_worldpos, wpos.x, wpos.y, wpos.z);
        glUniform1f(_mat_specular_intensity, intensity);
        glUniform1f(_specular_power, power);
    }

}
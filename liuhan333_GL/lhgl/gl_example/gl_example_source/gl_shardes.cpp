#include "gl_shardes.h"
#include "lhgl_util.h"
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
        _dirlight_colorlocation = get_uniformlocation(_shader_program, "gDirectionalLight.Base.Color");
        _dirlight_ambientintensitylocation = get_uniformlocation(_shader_program, "gDirectionalLight.Base.AmbientIntensity");
        _dirlight_directionlocation = get_uniformlocation(_shader_program, "gDirectionalLight.Direction");
        _dirlight_diffuseintensitylocation = get_uniformlocation(_shader_program, "gDirectionalLight.Base.DiffuseIntensity");

        _eye_worldpos = get_uniformlocation(_shader_program, "gEyeWorldPos");
        _mat_specular_intensity = get_uniformlocation(_shader_program, "gMatSpecularIntensity");
        _specular_power = get_uniformlocation(_shader_program, "gSpecularPower");

        uniform_point_lights_location();
        uniform_spot_lights_location();
        return true;
    }

    bool CShardes::uniform_spot_lights_location()
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

    bool CShardes::uniform_point_lights_location()
    {
        _numpoint_lights_location = get_uniformlocation(_shader_program, "gNumPointLights");
        int iszie = ARRAY_SIZE_IN_ELEMENTS(_point_lights_location);
        for (unsigned int i = 0; i < iszie; i++) 
        {
            char Name[128] = {0};
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

    void CShardes::gluniform_setpointlights(unsigned int num_lights, const PointLight* plights)
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

    void CShardes::gluniform_setspotlights(unsigned int NumLights, const SpotLight* pLights)
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
}
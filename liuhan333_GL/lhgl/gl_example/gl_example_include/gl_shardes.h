#ifndef GL_INCLUDE_GL_SHARDES_H
#define	GL_INCLUDE_GL_SHARDES_H
#include "lhgl_sharde_base.h"
#include "lhgl_lights_common.h"
namespace lh_gl {

    class CShardes :
        private CLHShardes
    {
    public:
        static const unsigned int MAX_POINT_LIGHTS = 2;
        static const unsigned int MAX_SPOT_LIGHTS = 2;
        
        CShardes();
        virtual ~CShardes();
    public:
        bool uniformlocation();
        bool glsharde_init(const char* cs_vs, const char* cs_fs);
        void gluniform_world_matrix_4fv(int, GLboolean, const GLfloat*);
        void gluniform_wvp_matrix_4fv(int, GLboolean, const GLfloat*);
        void gluniform_scale_1f(const float&);
        void gluniform_sampler_1i(const unsigned int&);
        void gluniform_light(const DirectionalLight&);
        void gluniform_specular_reflection(const Vector3f&, float, float);
        void gluniform_setpointlights(unsigned int, const PointLight*);
        void gluniform_setspotlights(unsigned int, const SpotLight*);
    private:
        bool uniform_point_lights_location();
        bool uniform_spot_lights_location();
    private:
        GLuint _shader_program;
        GLuint _scale_location;
        GLuint _world_location;
        GLuint _wvp_location;
        GLuint _sampler_location;
        GLuint _dirlight_colorlocation;
        GLuint _dirlight_ambientintensitylocation;
        GLuint _dirlight_directionlocation;
        GLuint _dirlight_diffuseintensitylocation;
        GLuint _eye_worldpos;
        GLuint _mat_specular_intensity;
        GLuint _specular_power;
    private:
        struct {
            GLuint Color;
            GLuint AmbientIntensity;
            GLuint DiffuseIntensity;
            GLuint Direction;
        } m_dirLightLocation;

        struct {
            GLuint Color;
            GLuint AmbientIntensity;
            GLuint DiffuseIntensity;
            GLuint Position;
            struct
            {
                GLuint Constant;
                GLuint Linear;
                GLuint Exp;
            } Atten;
        } _point_lights_location[MAX_POINT_LIGHTS];
        GLuint _numpoint_lights_location;

        struct {
            GLuint Color;
            GLuint AmbientIntensity;
            GLuint DiffuseIntensity;
            GLuint Position;
            GLuint Direction;
            GLuint Cutoff;
            struct {
                GLuint Constant;
                GLuint Linear;
                GLuint Exp;
            } Atten;
        } _spotLightsLocation[MAX_SPOT_LIGHTS];
        GLuint _numspot_lights_location;
    };
}

#endif

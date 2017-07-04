#ifndef GL_SHARDE_BASE_H
#define GL_SHARDE_BASE_H

#include <GL/glew.h>
#include <string>
#include "lhgl_lights_common.h"

namespace lh_gl {
    class CLHShardes
    {
    public:
        static const unsigned int MAX_POINT_LIGHTS = 2;
        static const unsigned int MAX_SPOT_LIGHTS = 2;

        CLHShardes(const char*, const char*);
        CLHShardes();
        virtual ~CLHShardes();

    public:
        void gluniform_directionlight(const DirectionalLight&);
        void gluniform_setpointlights(unsigned int, const PointLight*);
        void gluniform_setspotlights(unsigned int, const SpotLight*);
        void gluniform_world_matrix_4fv(int, GLboolean, const GLfloat*);
        void gluniform_wvp_matrix_4fv(int, GLboolean, const GLfloat*);
        void gluniform_scale_1f(const float&);
        void gluniform_sampler_1i(const unsigned int&);
        void gluniform_specular_reflection(const Vector3f&, float, float);
        virtual bool uniformlocation() = 0;
        virtual bool gl_enable() = 0;
        virtual bool gl_disable() = 0;
        virtual bool gl_drawelements(GLuint, GLuint) = 0;
        virtual bool glsharde_init(const char* cs_vs, const char* cs_fs);
    protected:
        bool get_uniformlocation(const GLuint shader_program, GLuint& getlication, const char* lication);
        GLuint get_uniformlocation(const GLuint shader_program, const char* lication);
        bool compile_shaders(GLuint&);
        bool uniform_point_lights_location();
        bool uniform_spot_lights_location();
        bool uniform_direction_lights_location();
        bool uniformlocation_base();
    private:
        void set_vs_filename(const char*);
        void set_fs_filename(const char*);
        bool add_shader(GLuint, const char*, GLenum);
    private:
        std::string str_vs_filename;
        std::string str_fs_filename;
        GLuint _scale_location;
        GLuint _world_location;
        GLuint _wvp_location;
        GLuint _sampler_location;
        GLuint _eye_worldpos;
        GLuint _mat_specular_intensity;
        GLuint _specular_power;
    protected:
            GLuint _shader_program;
    protected:
            struct {
            GLuint _dirlight_colorlocation;
            GLuint _dirlight_ambientintensitylocation;
            GLuint _dirlight_directionlocation;
            GLuint _dirlight_diffuseintensitylocation;
        } _direction_light_location;

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
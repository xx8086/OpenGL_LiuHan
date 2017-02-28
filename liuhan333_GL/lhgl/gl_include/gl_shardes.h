#ifndef GL_INCLUDE_GL_SHARDES_H
#define	GL_INCLUDE_GL_SHARDES_H
#include "lhsharde.h"
#include "lhgl_lights_common.h"
namespace lh_gl {

    class CShardes :
        private CLHShardes
    {
    public:
        //CShardes(const char*, const char*);
        CShardes();
        virtual ~CShardes();
    public:
        bool uniformlocation();
        bool glsharde_init();
        void gluniform_world_matrix_4fv(int, GLboolean, const GLfloat*);
        void gluniform_wvp_matrix_4fv(int, GLboolean, const GLfloat*);
        void gluniform_scale_1f(const float&);
        void gluniform_sampler_1i(const unsigned int&);
        void gluniform_light(const DirectionalLight&);
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
    };
}

#endif

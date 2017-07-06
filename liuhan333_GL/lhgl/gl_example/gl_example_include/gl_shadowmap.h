#ifndef GL_INCLUDE_GL_SHADOWMAP_H
#define	GL_INCLUDE_GL_SHADOWMAP_H

#include <GL/glew.h>
#include "gl_shardes.h"

namespace lh_gl {
    class CShadowMapFBO :
        public CShardes
    {
    public:
        CShadowMapFBO();
        ~CShadowMapFBO();

        bool init(unsigned int WindowWidth, unsigned int WindowHeight);
        void bindfoewriting();
        void bindtexture(GLenum TextureUnit);
    public:
        virtual bool gl_enable();
        virtual bool gl_disable();
        virtual bool gl_drawelements(GLuint, GLuint);
        virtual bool uniformlocation();
        virtual bool uniformlocation_base();
    public:
        void se_wvp(const Matrix4f& _wvp);
        void set_textureunit(unsigned int _tu);
    private:
        GLuint _fbo;
        GLuint _shadow_map;
        GLuint _texture_location;
        GLuint _wvp_location;
    };

}
#endif

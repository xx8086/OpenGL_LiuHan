#ifndef GL_INCLUDE_GL_SHADOWMAP_H
#define	GL_INCLUDE_GL_SHADOWMAP_H

#include <GL/glew.h>

namespace lh_gl {

    class CShadowMapFBO
    {
    public:
        CShadowMapFBO();
        ~CShadowMapFBO();

        bool Init(unsigned int WindowWidth, unsigned int WindowHeight);
        void BindForWriting();
        void BindForReading(GLenum TextureUnit);

    private:
        GLuint _fbo;
        GLuint _shadow_map;
    };

}
#endif

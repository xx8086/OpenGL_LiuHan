#include "gl_shadowmap.h"

namespace lh_gl {


    CShadowMapFBO::CShadowMapFBO()
    {
        _fbo = 0;
        _shadow_map = 0;
    }

    CShadowMapFBO::~CShadowMapFBO()
    {
        if (_fbo != 0) {
            glDeleteFramebuffers(1, &_fbo);
        }

        if (_shadow_map != 0) {
            glDeleteTextures(1, &_shadow_map);
        }
    }

    bool CShadowMapFBO::Init(unsigned int width, unsigned int height)
    {
        // Create the FBO
        glGenFramebuffers(1, &_fbo);

        // Create the depth buffer
        glGenTextures(1, &_shadow_map);
        glBindTexture(GL_TEXTURE_2D, _shadow_map);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadow_map, 0);

        // Disable writes to the color buffer
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if (Status != GL_FRAMEBUFFER_COMPLETE) {
            //printf("FB error, status: 0x%x\n", Status);
            return false;
        }

        return true;
    }


    void CShadowMapFBO::BindForWriting()
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
    }


    void CShadowMapFBO::BindForReading(GLenum TextureUnit)
    {
        glActiveTexture(TextureUnit);
        glBindTexture(GL_TEXTURE_2D, _shadow_map);
    }
}
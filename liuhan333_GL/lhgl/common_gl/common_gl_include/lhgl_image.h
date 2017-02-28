
#ifndef LHGL_IMAGE_TEXTURE_H
#define	LHGL_IMAGE_TEXTURE_H

#include <string>

#include <GL/glew.h>
#include <Magick++.h>

namespace lh_gl {
    class Texture
    {
    public:
        Texture(GLenum TextureTarget, const std::string& FileName);

        bool load_image();
        void bind_image(GLenum TextureUnit);

    private:
        std::string m_fileName;
        GLenum m_textureTarget;
        GLuint m_textureObj;
        Magick::Image m_image;
        Magick::Blob m_blob;
    };
}

#endif	/* TEXTURE_H */
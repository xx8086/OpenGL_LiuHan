#include "lhgl_util.h"
#include "lhgl_image.h"

namespace lh_gl {

    Texture::Texture(GLenum TextureTarget, const std::string& FileName)
    {
        m_textureTarget = TextureTarget;
        m_fileName = FileName;
    }

    bool Texture::load_image()
    {
        try {
            m_image.read(m_fileName);
            m_image.write(&m_blob, "RGBA");
        }
        catch (Magick::Error& Error) {
            LHGL_ERROR("Error loading texture %s: '%s'\n", m_fileName, Error.what());
            return false;
        }

        glGenTextures(1, &m_textureObj);
        glBindTexture(m_textureTarget, m_textureObj);
        glTexImage2D(m_textureTarget, 0, GL_RGBA, 
            m_image.columns(), m_image.rows(), 
            0, GL_RGBA, GL_UNSIGNED_BYTE, 
            m_blob.data());
        glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(m_textureTarget, 0);
        return true;
    }

    void Texture::bind_image(GLenum TextureUnit)
    {
        glActiveTexture(TextureUnit);
        glBindTexture(m_textureTarget, m_textureObj);
    }
}
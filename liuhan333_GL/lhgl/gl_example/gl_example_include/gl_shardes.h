#ifndef GL_INCLUDE_GL_SHARDES_H
#define	GL_INCLUDE_GL_SHARDES_H
#include "lhgl_sharde_base.h"
namespace lh_gl {

    class CShardes :
        public CLHShardes
    {
    public:
        CShardes();
        virtual ~CShardes();
    public:
        virtual bool gl_enable();
        virtual bool gl_disable();
        virtual bool gl_drawelements(GLuint, GLuint);
        virtual bool uniformlocation();
    public:
        bool glsharde_init(const char* cs_vs, const char* cs_fs);
        
    };
}

#endif

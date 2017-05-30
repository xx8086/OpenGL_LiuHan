
#include "lhgl_interface.h"
#include "GL\glew.h"
#include "glut.h"
#include "base_config.h"


namespace lh_gl_interface {
    LhGlInterfase::LhGlInterfase()
    {}

    LhGlInterfase::~LhGlInterfase()
    {}

    int LhGlInterfase::set_fps(function_time& cb, int t)
    {
       return timer.set_interval(cb, t);
    }

    bool LhGlInterfase::set_pixel(HDC hdc)
    {
        static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
        {
            sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
            1,											// Version Number
            PFD_DRAW_TO_WINDOW |						// Format Must Support Window
            PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
            PFD_DOUBLEBUFFER,							// Must Support Double Buffering
            PFD_TYPE_RGBA,								// Request An RGBA Format
            16,										// Select Our Color Depth
            0, 0, 0, 0, 0, 0,							// Color Bits Ignored
            0,											// No Alpha Buffer
            0,											// Shift Bit Ignored
            0,											// No Accumulation Buffer
            0, 0, 0, 0,									// Accumulation Bits Ignored
            16,											// 16Bit Z-Buffer (Depth Buffer)  
            0,											// No Stencil Buffer
            0,											// No Auxiliary Buffer
            PFD_MAIN_PLANE,								// Main Drawing Layer
            0,											// Reserved
            0, 0, 0										// Layer Masks Ignored
        };

        unsigned int pixelformat;
        FALSE_RT((pixelformat = ChoosePixelFormat(hdc, &pfd)), false)
            FALSE_RT(SetPixelFormat(hdc, pixelformat, &pfd), false)
            return true;
    }

    bool LhGlInterfase::set_glcontext(HDC hdc)
    {
        FALSE_RT((hrc = wglCreateContext(hdc)), false);
        FALSE_RT(wglMakeCurrent(hdc, hrc), false);
        return true;
    }

    bool LhGlInterfase::initialize(HDC hdc)
    {
        FALSE_RT(set_pixel(hdc), false);
        FALSE_RT(set_glcontext(hdc), false);

        _render.init();
        return true;
    }

    bool LhGlInterfase::drew()
    {
        _render.do_render();
        return true;
    }

    bool LhGlInterfase::relese()
    {
        if (hrc)
        {
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(hrc);
            hrc = nullptr;
        }
        return true;
    }

    bool LhGlInterfase::resize(unsigned short  width, unsigned short height)
    {
        glViewport(0, 0, width, height);						// Reset The Current Viewport

        glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
        glLoadIdentity();									// Reset The Projection Matrix
                                                            // Calculate The Aspect Ratio Of The Window
        gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
        glLoadIdentity();									// Reset The Modelview Matrix
        return true;
    }

    bool LhGlInterfase::lhgl_keyborad(bool bchar, unsigned int virtual_key, unsigned int utype)
    {
        return _render.specialkeyboard(bchar, virtual_key, utype);
    }

    bool LhGlInterfase::lhgl_mosuemove(unsigned int x, unsigned int y, unsigned int mark)
    {
        return  _render.onmouse(mark, x, y);
    }
}

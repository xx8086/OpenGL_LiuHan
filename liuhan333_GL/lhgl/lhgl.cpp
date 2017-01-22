// lhgl.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define DLL_EXPORTS
#include <string>
#include "lhgl.h"
#include "common_gl\lhgl_interface.h"

class ExportLHGL_Plus:
    public ExportLHGL, public Singleton<ExportLHGL_Plus>
{
public:
    virtual ~ExportLHGL_Plus() {};
    SINGLE_LH(ExportLHGL_Plus)
};

extern "C" DLL_API ExportLHGLInterface* get_lhglinstance()
{
    ExportLHGLInterface* pInstance = (ExportLHGL*)ExportLHGL_Plus::get_lhinstance();
    return pInstance;
}

bool ExportLHGL::lhgl_initialize(HDC hdc)
{
    return LhGlInterfase::get_lhinstance()->initialize(hdc);
}
bool ExportLHGL::lhgl_drew()
{
    return LhGlInterfase::get_lhinstance()->drew();
}
bool ExportLHGL::lhgl_drewsimple()
{
    return LhGlInterfase::get_lhinstance()->drewsimple();
}
bool ExportLHGL::lhgl_relese()
{
    return LhGlInterfase::get_lhinstance()->relese();
}
bool ExportLHGL::lhgl_resize(unsigned short  width, unsigned short height)
{
    return LhGlInterfase::get_lhinstance()->resize(width, height);
}


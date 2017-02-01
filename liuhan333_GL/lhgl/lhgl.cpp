// lhgl.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define DLL_EXPORTS
#include <string>
#include "lhgl.h"
#include "common_gl\lhgl_interface.h"

using namespace lh_gl_interface;

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

int ExportLHGL::lhgl_set_fps(function_time& bc, int t)
{
    return LhGlInterfase::get_lhinstance()->set_fps(bc, t);
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

bool ExportLHGL::lhgl_keyborad(bool bchar, unsigned int virtual_key, unsigned int utype)
{
    return LhGlInterfase::get_lhinstance()->lhgl_keyborad(bchar, virtual_key, utype);
}

bool ExportLHGL::lhgl_mosuemove(unsigned int x, unsigned int y, unsigned int mark)
{
    return LhGlInterfase::get_lhinstance()->lhgl_mosuemove(x, y, mark);
}



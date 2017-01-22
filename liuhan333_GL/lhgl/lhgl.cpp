// lhgl.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define DLL_EXPORTS
#include <string>
#include "lhgl.h"
#include "common_gl\lhgl_interface.h"

extern "C" DLL_API ExportLHGLInterface* getInstance()
{
    ExportLHGLInterface* pInstance = new ExportLHGL();
    return pInstance;
}

int ExportLHGL::add(int a, int b)
{
    //do something...
    return a + b;
}

bool ExportLHGL::Initialize(HDC hDC)
{
    return LhGlInterfase::GetInstance()->Initialize(hDC);
}
bool ExportLHGL::DrewSimple()
{
    return LhGlInterfase::GetInstance()->DrewSimple();
}
bool ExportLHGL::Relese()
{
    return LhGlInterfase::GetInstance()->Relese();
}
bool ExportLHGL::ReGLSize(unsigned short  width, unsigned short height)
{
    return LhGlInterfase::GetInstance()->ReGLSize(width, height);
}


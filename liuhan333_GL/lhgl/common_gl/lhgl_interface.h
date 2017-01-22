#pragma once
#include <Windows.h>
#include "singleton.h"



class LhGlInterfase:
    public Singleton<LhGlInterfase>
{
public:
    LhGlInterfase();
    virtual ~LhGlInterfase();
    SINGLE_LH(LhGlInterfase)
public:
	bool initialize(HDC);
    bool drew();
	bool drewsimple();
	bool relese();
	bool resize(unsigned short, unsigned short);
private:
	bool set_pixel(HDC);
	bool set_glcontext(HDC);
	bool init_gl();

private:
	HGLRC hrc = nullptr;
};


#pragma once
#include <Windows.h>
#include "singleton.h"

class LhGlInterfase:
    public Singleton<LhGlInterfase>
{
public:
    LhGlInterfase();
	virtual ~LhGlInterfase();
    static LhGlInterfase * GetInstance()
    {
        return &get_instance();
    }

private:
    class CGarbo
    {
    public:
        ~CGarbo()
        {
            destroy_instance();
        }
    };

    static CGarbo Garbo;
public:
	bool Initialize(HDC hDC);
	bool DrewSimple();
	bool Relese();
	bool ReGLSize(unsigned short  width, unsigned short height);
private:
	bool SetPixel(HDC hDC);
	bool SetGLContext(HDC hDC);
	bool InitGL();

private:
	HGLRC hRC = nullptr;
};


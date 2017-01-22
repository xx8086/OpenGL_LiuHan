#pragma once

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

class DLL_API ExportLHGLInterface
{
public:
    virtual bool lhgl_initialize(HDC) = 0;
    virtual bool lhgl_drewsimple() = 0;
    virtual bool lhgl_drew() = 0;
    virtual bool lhgl_relese() = 0;
    virtual bool lhgl_resize(unsigned short  width, unsigned short height) = 0;
};

extern "C" DLL_API ExportLHGLInterface*  get_lhglinstance();

#ifdef DLL_EXPORTS
class ExportLHGL : public ExportLHGLInterface
{
//private:
//    std::string x; //由于外部代码对此不可见，此处的std::string是安全的。
public:
    bool lhgl_initialize(HDC);
    bool lhgl_drew();
    bool lhgl_drewsimple();
    bool lhgl_relese();
    bool lhgl_resize(unsigned short, unsigned short);
};
#endif
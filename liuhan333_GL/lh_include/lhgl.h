#pragma once

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

class DLL_API ExportLHGLInterface
{
public:
    virtual int add(int a, int b) = 0;
    virtual bool Initialize(HDC hDC) = 0;
    virtual bool DrewSimple() = 0;
    virtual bool Relese() = 0;
    virtual bool ReGLSize(unsigned short  width, unsigned short height) = 0;
};

extern "C" DLL_API ExportLHGLInterface*  getInstance();

#ifdef DLL_EXPORTS
class ExportLHGL : public ExportLHGLInterface
{
//private:
//    std::string x; //由于外部代码对此不可见，此处的std::string是安全的。
public:
    int add(int a, int b);
    bool Initialize(HDC hDC);
    bool DrewSimple();
    bool Relese();
    bool ReGLSize(unsigned short  width, unsigned short height);
};
#endif
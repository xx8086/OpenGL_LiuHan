#include "lhgl_key_trans.h"

#ifdef _WIN32
#include <Windows.h>
//#include <Winuser.h>
#else
#endif


#ifdef _WIN32
LHGL_KEY virtual_key(unsigned int key)
{
    //https://msdn.microsoft.com/en-us/library/dd375731.aspx
    LHGL_KEY lh_gl_key = LHGL_KEY_NULL;
    switch (key)
    {
    case VK_INSERT:
        lh_gl_key = LHGL_KEY_INSERT;
        break;
    case VK_RETURN:
        lh_gl_key = LHGL_KEY_ENTER;
        break;
    case VK_ESCAPE:
        lh_gl_key = LHGL_KEY_ESCAPE;
        break;
    case VK_SPACE:
        lh_gl_key = LHGL_KEY_SPACE;
        break;
    case VK_TAB:
        lh_gl_key = LHGL_KEY_TAB;
        break;
    case VK_DELETE:
        lh_gl_key = LHGL_KEY_DELETE;
        break;
    case VK_LEFT:
        lh_gl_key = LHGL_KEY_LEFT;
        break;
    case VK_UP:
        lh_gl_key = LHGL_KEY_UP;
        break;
    case VK_RIGHT:
        lh_gl_key = LHGL_KEY_RIGHT;
        break;
    case VK_DOWN:
        lh_gl_key = LHGL_KEY_DOWN;
        break;
    case VK_PRIOR:
        lh_gl_key = LHGL_KEY_PAGE_UP;
        break;
    case VK_NEXT:
        lh_gl_key = LHGL_KEY_PAGE_DOWN;
        break;
    case VK_END:
        lh_gl_key = LHGL_KEY_END;
        break;
    case VK_HOME:
        lh_gl_key = LHGL_KEY_HOME;
        break;
    }

    return lh_gl_key;
}

LHGL_KEY char_key(unsigned int key)
{
    LHGL_KEY lh_gl_key = LHGL_KEY_NULL;
    //https://msdn.microsoft.com/en-us/library/dd375731.aspx
    if (key >= '0' && '9' >= key)
    {
        lh_gl_key = (LHGL_KEY)(key - '0' + LHGL_KEY_0);
    }
    else if (key >= 'A' && 'Z' >= key)
    {
        lh_gl_key = (LHGL_KEY)(key - 'A' + LHGL_KEY_A);
    }
    else if (key >= 'a' && 'z' >= key)
    {
        lh_gl_key = (LHGL_KEY)(key - 'a' + LHGL_KEY_a);
    }
    return lh_gl_key;
}

LHGL_KEY win32_to_glkey(bool bvk, unsigned int key)
{
    //https://msdn.microsoft.com/en-us/library/dd375731.aspx
    return bvk ? char_key(key): virtual_key(key);
}
#else
#endif

LHGL_KEY lh_to_glkey(bool bvk, unsigned int key)
{
    LHGL_KEY lh_gl_key = LHGL_KEY_NULL;
#ifdef _WIN32
    lh_gl_key = win32_to_glkey(bvk, key);
#else
#endif
    return lh_gl_key;
}

bool lh_mouse_move(unsigned int mark)
{
    bool rt = false;
#ifdef _WIN32
    /*
    #define MK_LBUTTON          0x0001
    #define MK_RBUTTON          0x0002
    #define MK_SHIFT            0x0004
    #define MK_CONTROL          0x0008
    #define MK_MBUTTON          0x0010
    */
    if (mark & MK_LBUTTON)
    {
        rt = true;
    }
#else
#endif

    return rt;
}
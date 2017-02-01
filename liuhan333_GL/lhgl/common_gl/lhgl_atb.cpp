#include "lhgl_atb.h"
#include "lhgl_lights_common.h"
#include "lhgl_math.h"

namespace lh_gl {
    TwType TW_TYPE_LHGL_VECTOR3F;
    TwType TW_TYPE_LHGL_ATTENUATION;

    ATB::ATB()
    {

    }


    bool ATB::Init()
    {
        bool ret = false;

        if (TwInit(TW_OPENGL_CORE, NULL) == 1)
        {
            TwStructMember Vector3fMembers[] = {
                { "x", TW_TYPE_FLOAT, offsetof(Vector3f, x), "" },
                { "y", TW_TYPE_FLOAT, offsetof(Vector3f, y), "" },
                { "z", TW_TYPE_FLOAT, offsetof(Vector3f, z), "" }
            };

            TW_TYPE_LHGL_VECTOR3F = TwDefineStruct("Vector3f", Vector3fMembers, 3, sizeof(Vector3f), NULL, NULL);

            TwStructMember AttenuationMembers[] = {
                { "Const", TW_TYPE_FLOAT, offsetof(LightAttenuation, Constant), "" },
                { "Linear", TW_TYPE_FLOAT, offsetof(LightAttenuation, Linear), "" },
                { "Exp", TW_TYPE_FLOAT, offsetof(LightAttenuation, Exp), "" }
            };

            TW_TYPE_LHGL_ATTENUATION = TwDefineStruct("Attenuation", AttenuationMembers, 3, sizeof(LightAttenuation), NULL, NULL);

            ret = true;
        }

        return ret;
    }


    static int OgldevKeyToATBKey(LHGL_KEY OgldevKey)
    {
        if (OgldevKey >= LHGL_KEY_SPACE && OgldevKey <= LHGL_KEY_RIGHT_BRACKET) {
            return OgldevKey;
        }

        switch (OgldevKey) {

        case LHGL_KEY_BACKSPACE:
            return TW_KEY_BACKSPACE;
        case LHGL_KEY_TAB:
            return TW_KEY_TAB;
            //            return TW_KEY_CLEAR;
        case LHGL_KEY_ENTER:
            return TW_KEY_RETURN;

            //return TW_KEY_PAUSE;
        case LHGL_KEY_ESCAPE:
            return TW_KEY_ESCAPE;
        case LHGL_KEY_DELETE:
            return TW_KEY_DELETE;
        case LHGL_KEY_UP:
            return TW_KEY_UP;
        case LHGL_KEY_DOWN:
            return TW_KEY_DOWN;
        case LHGL_KEY_RIGHT:
            return TW_KEY_RIGHT;
        case LHGL_KEY_LEFT:
            return TW_KEY_LEFT;
        case LHGL_KEY_INSERT:
            return TW_KEY_INSERT;
        case LHGL_KEY_HOME:
            return TW_KEY_HOME;
        case LHGL_KEY_END:
            return TW_KEY_END;
        case LHGL_KEY_PAGE_UP:
            return TW_KEY_PAGE_UP;
        case LHGL_KEY_PAGE_DOWN:
            return TW_KEY_PAGE_DOWN;
        case LHGL_KEY_F1:
            return TW_KEY_F1;
        case LHGL_KEY_F2:
            return TW_KEY_F2;
        case LHGL_KEY_F3:
            return TW_KEY_F3;
        case LHGL_KEY_F4:
            return TW_KEY_F4;
        case LHGL_KEY_F5:
            return TW_KEY_F5;
        case LHGL_KEY_F6:
            return TW_KEY_F6;
        case LHGL_KEY_F7:
            return TW_KEY_F7;
        case LHGL_KEY_F8:
            return TW_KEY_F8;
        case LHGL_KEY_F9:
            return TW_KEY_F9;
        case LHGL_KEY_F10:
            return TW_KEY_F10;
        case LHGL_KEY_F11:
            return TW_KEY_F11;
        case LHGL_KEY_F12:
            return TW_KEY_F12;
        default:
            LHGL_ERROR0("Unimplemented OGLDEV to ATB key");
        }

        return TW_KEY_LAST;
    }

    bool ATB::KeyboardCB(LHGL_KEY OgldevKey)
    {
        int ATBKey = OgldevKeyToATBKey(OgldevKey);

        if (ATBKey == TW_KEY_LAST) {
            return false;
        }

        return (TwKeyPressed(ATBKey, TW_KMOD_NONE) == 1);
    }


    bool ATB::PassiveMouseCB(int x, int y)
    {
        return (TwMouseMotion(x, y) == 1);
    }


    bool ATB::MouseCB(LHGL_MOUSE Button, LHGL_KEY_STATE State, int x, int y)
    {
        TwMouseButtonID btn = (Button == LHGL_MOUSE_BUTTON_LEFT) ? TW_MOUSE_LEFT : TW_MOUSE_RIGHT;
        TwMouseAction ma = (State == LHGL_KEY_STATE_PRESS) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;

        return (TwMouseButton(ma, btn) == 1);
    }
}
#ifndef LHGL_TAB_H
#define	LHGL_TAB_H

#include "lhgl_types.h"
#include "lhgl_keys.h"
#include "AntTweakBar.h"

namespace lh_gl {
    class ATB
    {
    public:
        ATB();

        bool Init();

        bool KeyboardCB(OGLDEV_KEY OgldevKey);

        bool PassiveMouseCB(int x, int y);

        void RenderSceneCB();

        bool MouseCB(OGLDEV_MOUSE Button, OGLDEV_KEY_STATE State, int x, int y);

    };


    extern TwType TW_TYPE_OGLDEV_VECTOR3F;
    extern TwType TW_TYPE_OGLDEV_ATTENUATION;
}
#endif

#pragma once
#include "gl_shardes.h"

namespace lh_gl {

    class CGlSample
    {
    public:
        CGlSample();
        virtual ~CGlSample();
    public:
        void do_render();
        bool init();
        bool onmouse(unsigned int mark, unsigned int x, unsigned int y);
        bool specialkeyboard(bool, unsigned int, unsigned int);

    private:
        void init_shardes();
    private:
        float vertex_postions[12] = {
            -1.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f};
        float vertex_colors[12] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.6f, 0.6f, 0.6f,
            0.0f, 0.0f, 1.0f,
        };
        unsigned int vertex_indices[12] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2 };
        unsigned int ebo;
        unsigned int vao;
        unsigned int bao;

        CShardes* _gl_shardes = nullptr;

    };
}
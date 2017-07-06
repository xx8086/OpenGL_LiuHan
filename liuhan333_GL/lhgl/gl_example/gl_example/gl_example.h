#pragma once
#include "gl_example_pyramid.h"
#include "gl_example_model_mx.h"
#include "gl_example_shadowmap.h"

//typedef lh_gl::CRanderExPyramid             EXAMPLE_CRENDER;
//typedef lh_gl::CRanderExModelMX             EXAMPLE_CRENDER;
typedef lh_gl::CRanderShadowMap             EXAMPLE_CRENDER;

inline lh_gl::CGlRenderBase* get_rend()
{
     return new EXAMPLE_CRENDER;
}
#ifndef LHGL_UTIL_H
#define	LHGL_UTIL_H

#ifndef WIN32
#include <unistd.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>
#include <assert.h>
#include "lhgl_types.h"

namespace lh_gl {
    using namespace std;

    bool read_file(const char* , string& );
    bool read_binaryfile(const char* , std::vector<int>& );

    void lhgl_error(const char* , uint , const char* , ...);
    void lhgl_file_error(const char* , uint , const char* );

#define LHGL_ERROR0(msg) lhgl_error(__FILE__, __LINE__, msg)
#define LHGL_ERROR(msg, ...) lhgl_error(__FILE__, __LINE__, msg, __VA_ARGS__)
#define LHGL_FILE_ERROR(FileError) lhgl_file_error(__FILE__, __LINE__, FileError);

#define ZERO_MEM(a) memset(a, 0, sizeof(a))
#define ZERO_MEM_VAR(var) memset(&var, 0, sizeof(var))
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#ifdef WIN32
#define SNPRINTF _snprintf_s
#define VSNPRINTF vsnprintf_s
#define RANDOM rand
#define SRANDOM srand((unsigned)time(NULL))
#if (_MSC_VER == 1900)
#elif (_MSC_VER == 1800)
#else
    float fmax(float a, float b);
#endif
#else
#define SNPRINTF snprintf
#define VSNPRINTF vsnprintf
#define RANDOM random
#define SRANDOM srandom(getpid())
#endif

#define INVALID_UNIFORM_LOCATION 0xffffffff
#define INVALID_LHGL_VALUE 0xffffffff

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

#define GLExitIfError                                                          \
{                                                                               \
    GLenum Error = glGetError();                                                \
                                                                                \
    if (Error != GL_NO_ERROR) {                                                 \
        printf("OpenGL error in %s:%d: 0x%x\n", __FILE__, __LINE__, Error);     \
        exit(0);                                                                \
    }                                                                           \
}

#define lhgl_check_error() (glGetError() == GL_NO_ERROR)

    long long get_curr_timemillis();


#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
}
#endif


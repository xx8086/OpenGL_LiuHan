#ifndef LHGL_TYPES_H
#define	LHGL_TYPES_H
#include "glm.hpp"

#ifndef WIN32
#include <unistd.h>
#endif

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef glm::ivec2 vec2i;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::quat quat;
typedef glm::mat4 mat4;

#endif


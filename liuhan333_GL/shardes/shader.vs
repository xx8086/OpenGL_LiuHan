#version 430

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;

uniform mat4 gwvp;
uniform mat4 gworld;

out vec2 texcoord0;
out vec3 normal0;
out vec3 WorldPos0;

void main()
{
    gl_Position = gwvp * vec4(Position, 1.0);
    texcoord0 = TexCoord;
    normal0 = (gworld * vec4(Normal, 0.0)).xyz;
    WorldPos0 = (gworld * vec4(Position, 1.0)).xyz;
}


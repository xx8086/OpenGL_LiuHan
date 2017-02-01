#version 430

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;

uniform mat4 gworld;
//out vec4 insert_color;
out vec2 texcoord0;

void main()
{
    gl_Position = gworld * vec4(Position, 1.0);
    //insert_color = vec4(clamp(Position, 0.0, 1.0), 1.0);
    texcoord0 = TexCoord;
}

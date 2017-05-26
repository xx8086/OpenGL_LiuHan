#version 430

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Colors;

uniform mat4 gworld;

out vec4 Color;

void main()
{
    gl_Position = gworld * vec4(Position, 1.0);
    //gl_Position = vec4(0.3 * Position.x, 0.3 * Position.y, Position.z, 1.0);
    Color = vec4(Colors, 1.0);
}

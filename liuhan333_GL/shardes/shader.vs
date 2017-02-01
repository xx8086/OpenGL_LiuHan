#version 430

layout (location = 0) in vec3 Position;

uniform mat4 gworld;
out vec4 insert_color;

void main()
{
    gl_Position = gworld * vec4(Position, 1.0);
    insert_color = vec4(clamp(Position, 0.0, 1.0), 1.0);
}

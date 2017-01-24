#version 430

in vec4 insert_color;
out vec4 FragColor;

void main()
{
    //FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    FragColor = insert_color;
}

#version 430

//in vec4 insert_color;
out vec4 FragColor;
in vec2 texcoord0;

uniform sampler2D gsampler;

void main()
{
    //FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    //FragColor = insert_color;
    FragColor = texture2D(gsampler, texcoord0.xy);
}

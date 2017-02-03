#version 430

out vec4 FragColor;
in vec2 texcoord0;

uniform sampler2D gsampler;

void main()
{
    FragColor = texture2D(gsampler, texcoord0.xy);
}

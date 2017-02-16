#version 430

in vec2 texcoord0;
out vec4 FragColor;

struct DirectionalLight
{
    vec3 Color;
    float AmbientIntensity;
};

uniform DirectionalLight gDirectionalLight;
uniform sampler2D gsampler;

void main()
{
    FragColor = vec4(gDirectionalLight.Color, 1.0f) * //环境光
	            texture2D(gsampler, texcoord0.xy) * //物体表面颜色
                gDirectionalLight.AmbientIntensity; //环境强度因素
}

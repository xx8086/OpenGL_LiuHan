#version 430

in vec2 texcoord0;
in vec3 normal0;
out vec4 FragColor;

struct DirectionalLight
{
    float AmbientIntensity;
    float DiffuseIntensity;  
    vec3 Color;
    vec3 Direction;
};

uniform DirectionalLight gDirectionalLight;
uniform sampler2D gsampler;

void main()
{
    vec4 ambien_color = vec4(gDirectionalLight.Color, 1.0f) *
                        gDirectionalLight.AmbientIntensity;
    float diffuse_factor = dot(normalize(normal0), -gDirectionalLight.Direction);
    vec4 diffuse_color = vec4(0, 0, 0, 0);
    if(diffuse_factor > 0)
    {
        diffuse_color = vec4(gDirectionalLight.Color, 1.0f) *
                        gDirectionalLight.DiffuseIntensity *
                        diffuse_factor;
    }

    FragColor = texture2D(gsampler, texcoord0.xy) *
                (ambien_color + diffuse_color);

}

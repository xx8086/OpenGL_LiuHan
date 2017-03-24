#version 430

struct DirectionalLight
{
    float AmbientIntensity;
    float DiffuseIntensity;  
    vec3 Color;
    vec3 Direction;
};

in vec2 texcoord0;
in vec3 normal0;
in vec3 WorldPos0;
out vec4 FragColor;

uniform DirectionalLight gDirectionalLight;
uniform sampler2D gsampler;

uniform vec3 gEyeWorldPos;
uniform float gMatSpecularIntensity;
uniform float gSpecularPower;

void main()
{
    vec3 normal_base = normalize(normal0);
    vec4 ambien_color = vec4(gDirectionalLight.Color, 1.0f) * gDirectionalLight.AmbientIntensity;//环境光
    float diffuse_factor = dot(normal_base, -gDirectionalLight.Direction);//光线与法线夹角余玄
    vec4 diffuse_color = vec4(0, 0, 0, 0);
    vec4 specular_color = vec4(0, 0, 0, 0);
    if(diffuse_factor > 0)
    {
        diffuse_color = vec4(gDirectionalLight.Color, 1.0f) *
                        gDirectionalLight.DiffuseIntensity *
                        diffuse_factor;//漫射光 = 光颜色*漫反射光强度*漫反射余玄

        vec3 vertex_eye = normalize(gEyeWorldPos - WorldPos0);
        vec3 light_reflect = normalize(reflect(gDirectionalLight.Direction, normal_base));
        float specularfactor = dot(vertex_eye, light_reflect);
        if (specularfactor > 0) 
        {
            specularfactor = pow(specularfactor, gSpecularPower);
            specular_color = vec4(gDirectionalLight.Color * gMatSpecularIntensity * specularfactor, 1.0f);
        }
    }

    FragColor = texture2D(gsampler, texcoord0.xy) *
                (ambien_color + diffuse_color + specular_color);

}

#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;
struct Light
{
    vec3 pos;
    vec3 col;
    vec3 dir;
};

struct MaterialLightInfo
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
    float shininess;
};

uniform sampler2D this_texture;
uniform bool texturing_enabled;
const float alpha_th = 0.1f;
uniform bool light_tex = false;
uniform Light world_light;
uniform MaterialLightInfo mat_light_info;
uniform vec3 view_pos;

vec4 computeLight(vec3 color, vec3 norm)
{
    vec3 ambient = 0.2 * color * mat_light_info.ambient;


    vec3 lightDir = normalize(-world_light.dir);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = color * (diff * mat_light_info.diffuse);

    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 viewDir = normalize(view_pos - fragPos);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
    vec3 specular = color * ((mat_light_info.shininess * spec) * mat_light_info.specular);

    vec3 result = ambient + diffuse + specular;
    return vec4(result, 1.0f);
}

void main()
{
    /*if (light_tex)
    {
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
        return;
    }*/
    //const int x = int(texFlags.x);
    if (texturing_enabled)
        FragColor = texture(this_texture, vec2(texCoord.x, -texCoord.y));
    else
        FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if (FragColor.a < alpha_th)
        discard;

    FragColor = computeLight(vec3(FragColor), normalize(normal));
    //FragColor = vec4(texCoord.x, texCoord.y, 1.0f, 1.0f);

}

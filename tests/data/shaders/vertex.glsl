#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 atexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 boneMat;
out vec2 texCoord;
out vec3 fragPos;
out vec3 normal;
void main()
{
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fragPos = vec3(model * vec4(aPos, 1.0));
    texCoord = atexCoord;
    normal = aNormal;
}

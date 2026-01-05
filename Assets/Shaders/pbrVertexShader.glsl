#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal; // make sure your VBO includes normals

out vec2 vUV;
out vec3 vNormal;
out vec3 vFragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vUV = aUV;
    vec4 worldPos = model * vec4(aPos, 1.0);
    vFragPos = worldPos.xyz;

    // Transform normal to world space
    vNormal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * worldPos;
}

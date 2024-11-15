#version 450

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 mvp;
uniform mat4 model;
uniform mat3 normalMatrix; // To transform normals to view space

out vec2 uv;
out vec3 fragNormal;
out vec3 fragPosition;

void main()
{
    // Transform vertex position
    gl_Position = mvp * vec4(vertexPosition, 1.0);

    // Pass the UV to the fragment shader
    uv = vertexUV;

    // Transform normal and position for lighting calculations
    fragNormal = normalize(normalMatrix * vertexNormal);
    fragPosition = vec3(model * vec4(vertexPosition, 1.0));
}
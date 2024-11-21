#version 450

layout(binding = 0) uniform sampler2D textureSampler;
uniform vec4 color;

in vec2 uv;
out vec4 fragColor;

void main()
{
    fragColor = texture(textureSampler, uv) * color;
}
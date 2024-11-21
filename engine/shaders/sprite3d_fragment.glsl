#version 450 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D textureSampler;
uniform vec4 color;
uniform int useTexture;

void main()
{
    if (useTexture != 0)
    {
        FragColor = texture(textureSampler, TexCoords);
    }
    else
    {
        FragColor = color;
    }
}
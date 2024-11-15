#version 450

layout(binding = 0) uniform sampler2D textureSampler;

in vec2 uv;
in vec3 fragNormal;
in vec3 fragPosition;

out vec4 fragColor;

// Light and material properties
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor = vec3(1.0);
uniform vec3 ambientColor = vec3(0.1, 0.1, 0.1);
uniform vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
uniform vec3 specularColor = vec3(1.0, 1.0, 1.0);
uniform float shininess = 32.0;

void main()
{
    // Sample the texture
    vec4 textureColor = texture(textureSampler, uv);

    // Ambient component
    vec3 ambient = ambientColor * lightColor;

    // Diffuse component
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseColor * lightColor;

    // Specular component
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * specularColor * lightColor;

    // Combine all components
    vec3 lighting = ambient + diffuse + specular;
    fragColor = vec4(lighting, 1.0) * textureColor;
}
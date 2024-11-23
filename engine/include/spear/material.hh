#ifndef SPEAR_MATERIAL_HH
#define SPEAR_MATERIAL_HH

#include <spear/rendering/opengl/shader.hh>
#include <spear/rendering/opengl/texture.hh>

#include <glm/vec3.hpp>

namespace spear
{

class Material
{
public:
    /// Constructor.
    Material(rendering::opengl::Shader& shader, rendering::opengl::Texture& texture);

    int32_t getProgram() { return m_shader.getId(); }

    rendering::opengl::Texture& getTexture()
    {
        return m_texture;
    }

    const int32_t& getColor() const { return m_color; }
    const int32_t& getMvp() const { return m_mvp; }
    const int32_t& getSampler() const { return m_sampler; }

    void use();
private:
    rendering::opengl::Shader& m_shader;
    rendering::opengl::Texture& m_texture;
    int32_t m_mvp;
    int32_t m_color;
    int32_t m_sampler;
};

}

#endif

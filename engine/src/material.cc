#include <spear/rendering/opengl/shader.hh>
#include <spear/material.hh>

#include <GL/glew.h>

namespace spear
{

Material::Material(std::shared_ptr<rendering::opengl::Shader> shader, rendering::opengl::Texture&& texture)
    : m_shader(std::unique_ptr<rendering::opengl::Shader>(shader.get())),
      m_texture(std::move(texture)),
      m_mvp(glGetUniformLocation(shader->getId(), "mvp")),
      m_color(glGetUniformLocation(shader->getId(), "color"))
{
}

const uint32_t& Material::getColor() const { return m_color; }

void Material::use() { glUseProgram(m_shader->getId()); }

}

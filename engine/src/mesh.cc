#include "spear/material.hh"
#include <spear/mesh.hh>

namespace spear
{

Mesh::Mesh(std::shared_ptr<spear::rendering::OpenGLShader> shader, Texture&& texture, const glm::vec3& color)
    : m_material(shader, std::move(texture)),
      m_color(color)
{
}

}
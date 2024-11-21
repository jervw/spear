#include "spear/transform.hh"
#include <spear/mesh.hh>

namespace spear
{

Mesh::Mesh(spear::rendering::opengl::Shader& shader, rendering::opengl::Texture& texture, const glm::vec3& color)
    : m_material(shader, texture, color)
{
}

}

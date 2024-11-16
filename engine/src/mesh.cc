#include <spear/mesh.hh>

namespace spear
{

Mesh::Mesh(std::shared_ptr<spear::rendering::opengl::Shader> shader, rendering::opengl::Texture&& texture)
    : m_material(shader, std::move(texture))
{
}

}

#include <spear/mesh.hh>

namespace spear
{

Mesh::Mesh(std::shared_ptr<rendering::BaseShader> shader)
    : m_shader(std::move(shader))
{
}

Mesh::Mesh(std::shared_ptr<rendering::BaseShader> shader, std::shared_ptr<rendering::BaseTexture> texture)
    : m_shader(std::move(shader)),
      m_texture(std::move(texture))
{
}


}

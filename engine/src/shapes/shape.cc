#include <spear/shapes/shape.hh>

namespace spear
{

Shape::Shape(rendering::opengl::Shader& shader, rendering::opengl::Texture& texture, const glm::vec3& color)
    : Mesh(shader, texture, color)
{
}

}

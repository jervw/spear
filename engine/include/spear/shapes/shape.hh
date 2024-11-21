#ifndef SPEAR_SHAPE_SHAPE_HH
#define SPEAR_SHAPE_SHAPE_HH

#include <spear/mesh.hh>
#include <spear/entity.hh>

namespace spear
{

class Shape : public Mesh, public Entity
{
public:
    explicit Shape(rendering::opengl::Shader& shader, rendering::opengl::Texture& texture, const glm::vec3& color);
};

}

#endif

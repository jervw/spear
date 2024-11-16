#ifndef SPEAR_SHAPE_HH
#define SPEAR_SHAPE_HH

#include <spear/shapes/shape.hh>
#include <spear/rendering/opengl/texture.hh>
#include <spear/camera.hh>

namespace spear
{

class Cube : public Shape
{
public:
    //Cube(rendering::opengl::Texture&& texture, const glm::vec3& color);

    // Mesh::render implementation.
    void render(Camera& camera) override;
};

}

#endif

#ifndef SPEAR_MESH_HH
#define SPEAR_MESH_HH

#include <spear/rendering/opengl/shader.hh>
#include <spear/rendering/opengl/texture.hh>
#include <spear/material.hh>
#include <spear/camera.hh>

#include <glm/vec3.hpp>

namespace spear
{

class Mesh
{
public:
    // OpenGL constructor. TODO Construct for all api types.
    explicit Mesh(rendering::opengl::Shader& shader, rendering::opengl::Texture& texture, const glm::vec3& color);

    virtual void render(Camera& camera) = 0;
protected:
    Material m_material;
    glm::vec3 m_color;
};

}

#endif

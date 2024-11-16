#ifndef SPEAR_MESH_HH
#define SPEAR_MESH_HH

#include <spear/rendering/opengl/shader.hh>
#include <spear/rendering/opengl/texture.hh>
#include <spear/material.hh>
#include <spear/camera.hh>
#include <spear/rendering/opengl/texture.hh>
#include <spear/rendering/api.hh>
#include <spear/rendering/base_shader.hh>

#include <glm/vec3.hpp>

#include <memory>

namespace spear
{

class Mesh
{
public:
    // OpenGL constructor. TODO Construct for all api types.
    explicit Mesh(std::shared_ptr<rendering::opengl::Shader> shader, rendering::opengl::Texture&& texture);

    virtual void render(Camera& camera);
private:
    Material m_material;
    glm::vec3 m_color;
};

}

#endif

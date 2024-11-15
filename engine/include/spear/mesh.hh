#ifndef SPEAR_MESH_HH
#define SPEAR_MESH_HH

#include <spear/rendering/opengl/opengl_shader.hh>
#include <spear/material.hh>

#include <glm/vec3.hpp>

namespace spear
{

class Mesh
{
public:
    Mesh(std::shared_ptr<spear::rendering::OpenGLShader>, Texture&& texture, const glm::vec3& color);

private:
    Material m_material;
    glm::vec3 m_color;
};

}

#endif
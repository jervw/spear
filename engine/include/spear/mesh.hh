#ifndef SPEAR_MESH_HH
#define SPEAR_MESH_HH

#include <spear/camera.hh>
#include <spear/material.hh>

#include <spear/rendering/base_shader.hh>
#include <spear/rendering/base_texture.hh>

namespace spear
{

class Mesh
{
public:
    explicit Mesh(std::shared_ptr<rendering::BaseShader> shader);

    virtual void render(Camera& camera) = 0;

protected:
    std::shared_ptr<rendering::BaseShader> m_shader;
};

} // namespace spear

#endif

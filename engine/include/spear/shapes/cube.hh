#ifndef SPEAR_SHAPE_HH
#define SPEAR_SHAPE_HH

#include <spear/shapes/shape.hh>
#include <spear/rendering/opengl/texture.hh>
#include <spear/camera.hh>

#include <vector>

namespace spear
{

class Cube : public Shape
{
public:
    Cube(rendering::opengl::Shader& shader, rendering::opengl::Texture& texture, const glm::vec3& color);

    // Mesh::render implementation.
    void render(Camera& camera) override;

    /// Transform::translate implementation.
    void translate(const glm::vec3& position) override
    {

    }

private:
    std::vector<float> createVertexBufferData(const glm::vec3& v);
    std::vector<float> createUvData();
    void create(std::vector<float>&& vertexBufferData, std::vector<float>&& uvData);

private:
    uint32_t m_vao;
    glm::vec3 m_color;
    uint32_t m_vertexDataSize;
    uint32_t m_uvDataSize;
};

}

#endif

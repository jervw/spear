#ifndef SPEAR_CUBE2_HH
#define SPEAR_CUBE2_HH

#include <spear/rendering/opengl/shader.hh>
#include <spear/shapes/shape.hh>

#include <vector>

namespace spear
{

class Quad : public Shape
{
public:
    /// Constructor.
    Quad(std::shared_ptr<spear::rendering::BaseShader> m_shader, size_t size, const glm::vec3& color);

    /// Destructor.
    ~Quad();

    void free();

    void initialize(const glm::vec3& position);

    /// Transform::translate implementation.
    void translate(const glm::vec3& position) override;

    //void render(const glm::mat4& view, const glm::mat4& projection);
    /// Mesh::render implementation.
    void render(Camera& camera) override;

private:
    size_t m_size;
    glm::vec3 m_color;
    uint32_t m_vao, m_vbo, m_ebo;
    std::vector<float> m_vertices;
};

}

#endif

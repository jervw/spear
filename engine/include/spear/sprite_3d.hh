#ifndef SPEAR_SPRITE_3D_HH
#define SPEAR_SPRITE_3D_HH

#include <spear/rendering/base_texture.hh>
#include <spear/rendering/opengl/shader.hh>
#include <spear/rendering/opengl/shader.hh>
#include <spear/rendering/opengl/texture.hh>
#include <spear/rendering/opengl/error.hh>

#include <spear/transform.hh>
#include <spear/mesh.hh>

namespace spear
{

class Sprite3D : public Mesh, public Transform
{
public:
    // Constructor with texture.
    Sprite3D(std::shared_ptr<rendering::BaseShader> shader, std::shared_ptr<rendering::BaseTexture> texture, glm::vec3 position);

    // Constructor with color.
    Sprite3D(std::shared_ptr<rendering::BaseShader> shader, glm::vec3 position, glm::vec4 color);

    // Destructor.
    ~Sprite3D();

    /// Mesh::render implementation.
    void render(Camera& camera) override;

    void setPosition(const glm::vec3& newPosition)
    {
        m_position = newPosition;
    }

    void setSize(const glm::vec2& newSize)
    {
        m_size = newSize;
    }

    void setRotation(float newRotation)
    {
        m_rotation = newRotation;
    }

protected:
    void init();
    void setUseTexture();
private:
    // Input data.
    glm::vec3 m_position;
    glm::vec4 m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec2 m_size;
    float m_rotation; // degrees

    // Vertex Array Object, Vertex Buffer Object, Element Buffer Object.
    uint32_t m_vao = 0, m_vbo = 0, m_ebo = 0;

    // Vertices for a quad.
    const float m_vertices[20] = {
        // Positions        // Texture Coords
        0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f
    };

    const uint32_t m_indices[6]
    {
        0, 1, 2,
        2, 3, 0
    };

    int32_t m_sampler;
    bool m_useTexture;
};

}

#endif

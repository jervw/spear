#include <spear/rendering/base_shader.hh>
#include <spear/sprite_3d.hh>

namespace spear
{

Sprite3D::Sprite3D(std::shared_ptr<rendering::BaseShader> shader, std::shared_ptr<rendering::BaseTexture> texture, glm::vec3 position)
    : Mesh(shader, texture), Transform(),
      m_position(position), m_color(-1), m_sampler(GL_TEXTURE_2D), m_useTexture(true)
{
    setUseTexture();
    init();
}

Sprite3D::Sprite3D(std::shared_ptr<rendering::BaseShader> shader, glm::vec3 position, glm::vec4 color)
    : Mesh(shader), Transform(),
      m_position(position), m_color(color), m_sampler(-1), m_useTexture(false)
{
    setUseTexture();
    init();
}

Sprite3D::~Sprite3D()
{
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
}

void Sprite3D::render(Camera& camera)
{
    m_shader->use();

    // Model matrix
    /*
    glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
    model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(m_size, 1.0f));
    */

    glm::mat4 mvp = Transform::getModel() * camera.getViewMatrix() * camera.getProjectionMatrix();
    m_shader->setMat4("mvp", mvp);

    if (m_useTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        m_shader->setSampler2D("textureSampler", 0);

        //assert(m_shader->get)

        m_texture->bind();
    }
    else
    {
        m_shader->setVec4f("color", m_color);
    }

    // Render quad
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sprite3D::init()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Sprite3D::setUseTexture()
{
    if (m_useTexture)
    {
        m_shader->setInt("useTexture", 1);
    }
    else
    {
        m_shader->setInt("useTexture", 0);
    }
}

}

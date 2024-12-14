#include <spear/rendering/base_shader.hh>
#include <spear/sprite_3d.hh>

namespace spear
{

Sprite3D::Sprite3D(glm::vec3 position)
    : Mesh(std::shared_ptr<rendering::BaseShader>(rendering::opengl::Shader::create(rendering::ShaderType::sprite3D))), Transform(),
      m_position(position), m_sampler(GL_TEXTURE_2D)
{
}

Sprite3D::~Sprite3D()
{
    if (m_vao)
        glDeleteVertexArrays(1, &m_vao);
    if (m_vbo)
        glDeleteBuffers(1, &m_vbo);
    if (m_ebo)
        glDeleteBuffers(1, &m_ebo);
}

void Sprite3D::render(Camera& camera)
{
    Mesh::m_shader->use();
    glm::mat4 mvp = Transform::getModel() * camera.getViewMatrix() * camera.getProjectionMatrix();
    m_shader->setMat4("mvp", mvp);

    // Ensure texture is bound to unit 0
    glActiveTexture(GL_TEXTURE0);
    m_texture.bind();
    m_shader->setSampler2D("textureSampler", 0);

    // Render quad
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Sprite3D::initialize()
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

void Sprite3D::loadImage(const std::string& path)
{
    m_texture.loadFile(path);
    m_texture.bind();
}

} // namespace spear

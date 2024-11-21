#ifndef SPEAR_CUBE2_HH
#define SPEAR_CUBE2_HH

#include <spear/rendering/opengl/shader.hh>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace spear
{

class Quad
{
public:
    Quad() : m_shader(rendering::opengl::Shader(rendering::ShaderType::quad)),
    m_vao(0), m_vbo(0), m_ebo(0) {}

    ~Quad() {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ebo);
    }

    void initialize() {
        // Vertex data for a cube
        float vertices[] = {
            // Positions          // Colors
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // Bottom-left
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // Bottom-right
             0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // Top-right
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // Top-left
            -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // Bottom-left (back)
             0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Bottom-right (back)
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // Top-right (back)
            -0.5f,  0.5f,  0.5f,  0.2f, 0.8f, 0.2f  // Top-left (back)
        };

        // Indices for the cube
        unsigned int indices[] = {
            0, 1, 2, 2, 3, 0,   // Front face
            4, 5, 6, 6, 7, 4,   // Back face
            0, 1, 5, 5, 4, 0,   // Bottom face
            3, 2, 6, 6, 7, 3,   // Top face
            0, 3, 7, 7, 4, 0,   // Left face
            1, 2, 6, 6, 5, 1    // Right face
        };

        // Create VAO, VBO, and EBO
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        glBindVertexArray(m_vao);

        // Upload vertex data
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Upload index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Set vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // Positions
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Colors
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        m_shader.createShaderProgram(m_shader.getVertexId(), m_shader.getFragmentId());
    }

    void render(const glm::mat4& view, const glm::mat4& projection)
    {
        m_shader.use();

        // Calculate Model-View-Projection matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp = projection * view * model;

        // Send MVP matrix to the shader
        GLuint mvpLocation = glGetUniformLocation(m_shader.getId(), "mvp");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

        // Render the cube
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    spear::rendering::opengl::Shader m_shader;
    GLuint m_vao, m_vbo, m_ebo;
};

}

#endif
#ifndef SPEAR_SPRITE_3D_HH
#define SPEAR_SPRITE_3D_HH

#include <spear/rendering/base_texture.hh>
#include <spear/rendering/opengl/shader.hh>
#include <spear/rendering/opengl/shader.hh>
#include <spear/rendering/opengl/texture.hh>
#include <spear/rendering/opengl/error.hh>
#include <spear/mesh.hh>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <iostream>

namespace spear
{

class Sprite3D : public Mesh
{
public:
    // Constructor with texture.
    Sprite3D(std::shared_ptr<rendering::BaseShader> shader, std::shared_ptr<rendering::BaseTexture> texture, glm::vec3 position, glm::vec2 size, float rotation = 0.0f)
        : Mesh(shader), m_position(position), m_size(size), m_rotation(rotation), m_color(-1), m_sampler(-1), m_useTexture(true)
    {
        setUseTexture();
        initializeUniforms();
        init();
    }

    // Constructor with color.
    Sprite3D(std::shared_ptr<rendering::BaseShader> shader, glm::vec3 position, glm::vec2 size, glm::vec3 color, float rotation = 0.f)
        : Mesh(shader), m_position(position), m_size(size), m_rotation(rotation), m_color(-1), m_sampler(-1), m_useTexture(false)
    {
        setUseTexture();
        initializeUniforms();
        init();
    }

    ~Sprite3D()
    {
        if (m_vao) glDeleteVertexArrays(1, &m_vao);
        if (m_vbo) glDeleteBuffers(1, &m_vbo);
        if (m_ebo) glDeleteBuffers(1, &m_ebo);
    }

    void render(const glm::mat4& view, const glm::mat4& projection)
    {
        m_shader->use();

        // Model matrix
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_position);
        model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(m_size, 1.0f));
        glm::mat4 mvp = projection * view * model;

        // Send MVP to matrix
        glUniformMatrix4fv(m_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

        if (m_useTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            m_texture->bind();
            glUniform1i(m_sampler, 0);
        }
        else
        {
            glUniform4f(m_color, 1.0f, 1.0f, 1.0f, 1.0f);
        }

        // Render quad
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

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

private:
    void init()
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

    void initializeUniforms()
    {
        m_mvp = glGetUniformLocation(m_shader->getId(), "mvp");
        m_color = glGetUniformLocation(m_shader->getId(), "color");
        m_sampler = glGetUniformLocation(m_shader->getId(), "textureSampler");

        if (m_mvp == -1) std::cerr << "Error: Uniform 'mvp' not found in shader program." << std::endl;
        if (!m_useTexture && m_color == -1) std::cerr << "Error: Uniform 'color' not found in shader program." << std::endl;
        if (m_useTexture && m_sampler == -1) std::cerr << "Error: Uniform 'textureSampler' not found in shader program." << std::endl;
    }

    void setUseTexture()
    {
        GLint useTextureLocation = glGetUniformLocation(m_shader->getId(), "useTexture");
        if (useTextureLocation == -1)
        {
            std::cerr << "Error: Uniform 'useTexture' not found in shader program." << std::endl;
        }
        else
        {
            if (m_useTexture)
            {
                glUniform1i(useTextureLocation, 1);
            }
            else
            {
                glUniform1i(useTextureLocation, 0);
            }
        }
    }

private:
    // Input data.
    glm::vec3 m_position;
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

    int32_t m_mvp;
    int32_t m_color;
    int32_t m_sampler;
    bool m_useTexture;
};

}

#endif

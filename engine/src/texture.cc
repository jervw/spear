#include "spear/rendering/opengl/opengl_shader.hh"
#include <spear/texture.hh>

#include <SDL3_image/SDL_image.h>

namespace spear
{

Texture::Texture(std::shared_ptr<rendering::OpenGLShader> shader, const std::string& file_path)
    : m_shader(std::unique_ptr<rendering::Shader>(shader.get())),
      m_file_path(file_path)
{
}

Texture::Texture(Texture&& other)
    : m_shader(std::move(other.m_shader)),
      m_file_path(std::move(other.m_file_path)),
      m_texture(std::move(other.m_texture)),
      m_width(std::move(other.m_width)),
      m_height(std::move(other.m_height))
{
}

Texture& Texture::operator=(Texture&& other)
{
    if (this != &other)
    {
        m_shader = std::move(other.m_shader);
        m_file_path = std::move(other.m_file_path);
        m_texture = std::move(other.m_texture);
        m_width = std::move(other.m_width);
        m_height = std::move(other.m_height);
    }
    return *this;
}

}
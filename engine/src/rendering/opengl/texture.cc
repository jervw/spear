#include <spear/rendering/opengl/texture.hh>

#include <SDL3_image/SDL_image.h>
#include <GL/glew.h>

#include <iostream>

namespace spear::rendering::opengl
{

Texture::Texture()
    : m_id(0),
      m_width(0),
      m_height(0)
{
}

Texture::Texture(Texture&& other)
    : m_id(std::move(other.m_id)),
      m_width(std::move(other.m_width)),
      m_height(std::move(other.m_height))
{
}

Texture& Texture::operator=(Texture&& other)
{
    if (this != &other)
    {
        m_id = std::move(other.m_id);
        m_width = std::move(other.m_width);
        m_height = std::move(other.m_height);
    }
    return *this;
}

// Load texture from file (expects an external renderer setup)
bool Texture::loadFromFile(const std::string& path)
{
    free();

    // Load image using SDL
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load image: " << path 
                  << " | SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Determine the format
    GLenum format = GL_RGBA;

    // Generate OpenGL texture
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload texture data to GPU
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        surface->w,
        surface->h,
        0,
        format,
        GL_UNSIGNED_BYTE,
        surface->pixels
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    // Store dimensions
    m_width = surface->w;
    m_height = surface->h;

    // Unbind texture and free image data
    SDL_DestroySurface(surface);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

void Texture::bind(uint32_t unit) const
{
    if (m_id == 0) {
        std::cerr << "Attempted to bind an uninitialized texture." << std::endl;
        return;
    }
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void unbind(uint32_t unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::free()
{
    if (m_id)
    {
        glDeleteTextures(1, &m_id);
        m_id = 0;
        m_width = 0;
        m_height = 0;
    }
}

}

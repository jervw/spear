#ifndef SPEAR_TEXTURE_HH
#define SPEAR_TEXTURE_HH

#include "spear/rendering/opengl/opengl_shader.hh"
#include <SDL3/SDL_render.h>

#include <spear/rendering/shader.hh>

#include <string>
#include <memory>

namespace spear
{

class Texture
{
public:
    /// Constructor.
    Texture(std::shared_ptr<rendering::OpenGLShader> shader, const std::string& file_path);
    //Texture(const std::string& file_path, std::shared_ptr<rendering::VulkanShader> shader);

    /// Destructor.
    ~Texture();

    /// Move constructor.
    Texture(Texture&& other);

    /// Move assignment operator.
    Texture& operator=(Texture&& other);

    /// Deleted copy constructor.
    Texture(const Texture&) = delete;

    /// Deleted copy assignment.
    Texture& operator=(const Texture&) = delete;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    bool isLoaded() const { return m_texture != nullptr; }

private:
    std::unique_ptr<rendering::Shader> m_shader;
    std::string m_file_path;
    SDL_Texture* m_texture;
    float m_width;
    float m_height;
};

}

#endif
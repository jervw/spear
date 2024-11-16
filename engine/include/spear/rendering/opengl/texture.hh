#ifndef SPEAR_TEXTURE_HH
#define SPEAR_TEXTURE_HH

#include <cstdint>
#include <string>

namespace spear::rendering::opengl
{

class Texture
{
public:
    /// Constructor.
    Texture();

    /// Destructor.
    ~Texture()
    {
        free();
    }

    /// Move constructor.
    Texture(Texture&& other);

    /// Move assignment operator.
    Texture& operator=(Texture&& other);

    /// Deleted copy constructor.
    Texture(const Texture&) = delete;

    /// Deleted copy assignment.
    Texture& operator=(const Texture&) = delete;

    // Load texture from file.
    bool loadFromFile(const std::string& path);

    // Bind texture
    void bind(uint32_t unit = 0) const;

    // Unbind texture
    static void unbind(uint32_t unit = 0);

    // Free texture
    void free();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

private:
    uint32_t m_id;
    float m_width;
    float m_height;
};

}

#endif
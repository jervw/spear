#ifndef SPEAR_RENDERING_BASE_TEXTURE_HH
#define SPEAR_RENDERING_BASE_TEXTURE_HH

#include <cstdint>

namespace spear::rendering
{

class BaseTexture
{
public:
    BaseTexture(uint32_t id);

    /// Move constructor.
    BaseTexture(BaseTexture&& other);

    /// Move assignment operator.
    BaseTexture& operator=(BaseTexture&& other);

    /// Copy constructor.
    BaseTexture(const BaseTexture& other);

    /// Copy assignment operator.
    BaseTexture& operator=(const BaseTexture& other);

    virtual ~BaseTexture(){}
    virtual void bind(uint32_t unit = 0) const = 0;

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    uint32_t getId() const { return m_id; }
    uint32_t* getIdPtr() { return &m_id; }

protected:
    uint32_t m_id;
    float m_width;
    float m_height;
};

}

#endif

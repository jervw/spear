#ifndef SPEAR_SHADER_HH
#define SPEAR_SHADER_HH

#include <string>
#include <cstdint>

#include <glm/mat4x4.hpp>

namespace spear::rendering
{

class BaseShader
{
public:
    /// Constructor.
    BaseShader() = default;

    /// Move constructor.
    BaseShader(BaseShader&& other);

    /// Move assignment operator.
    BaseShader& operator=(BaseShader&& other);

    /// Deleted copy constructor.
    BaseShader(const BaseShader&) = delete;

    /// Deleted copy assignment operator.
    BaseShader& operator=(const BaseShader&) = delete;

    /// Destructor.
    virtual ~BaseShader();

    uint32_t getId() const
    {
        return m_id;
    }

    bool isProgramLinked() const
    {
        return m_id != 0;
    }

    virtual void setMat4(const std::string&, const glm::mat4&) = 0;
    virtual void use() = 0;
    virtual void createShaderProgram(uint32_t, uint32_t) = 0;

protected:
    void checkCompileErrors(uint32_t shader, const std::string& type);

    void setId(uint32_t id)
    {
        m_id = id;
    }

private:
    uint32_t m_id = 0;
};

}

#endif

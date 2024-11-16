#ifndef SPEAR_SHADER_HH
#define SPEAR_SHADER_HH

#include <string>
#include <cstdint>

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

protected:
    void checkCompileErrors(uint32_t shader, std::string type);

    virtual uint32_t createShaderProgram(int, int){ return 0; }

    void setId(uint32_t id)
    {
        m_id = id;
    }

private:
	uint32_t m_id;
};

}

#endif
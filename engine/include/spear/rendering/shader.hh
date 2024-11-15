#ifndef SPEAR_SHADER_HH
#define SPEAR_SHADER_HH

#include <string>
#include <cstdint>

namespace spear::rendering
{

class Shader
{
public:
	/// Constructor.
    Shader() = default;

    /// Move constructor.
    Shader(Shader&& other);

    /// Move assignment operator.
    Shader& operator=(Shader&& other);

    /// Deleted copy constructor.
    Shader(const Shader&) = delete;

    /// Deleted copy assignment operator.
    Shader& operator=(const Shader&) = delete;

    /// Destructor.
	virtual ~Shader();

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
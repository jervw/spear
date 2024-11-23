#ifndef SPEAR_RENDERING_OPENGL_SHADER_HH
#define SPEAR_RENDERING_OPENGL_SHADER_HH

#include <spear/rendering/base_shader.hh>
#include <spear/rendering/shader_type.hh>

#include <memory>

namespace spear::rendering::opengl
{

class Shader : public BaseShader
{
public:
    /// Constructor.
    Shader(ShaderType shader_type);

    /// Destructor.
    ~Shader();

    /// Move constructor.
    Shader(Shader&& other);

    /// Move assignment operator.
    Shader& operator=(Shader&& other);

    /// Deleted copy constructor.
    Shader(const Shader&) = delete;

    /// Deleted copy assignment operator.
    Shader& operator=(const Shader&) = delete;

    static std::shared_ptr<Shader> create(ShaderType shader_type)
    {
        return std::make_shared<Shader>(Shader(shader_type));
    }

    void setMat4(const std::string& name, const glm::mat4& mat) override;
    void use() override;
    void createShaderProgram() override;

    int getVertexId() const { return m_vertexId; }
    int getFragmentId() const { return m_fragmentId; }

private:
    std::string m_vertexCode;
    std::string m_fragmentCode;
    uint32_t m_vertexId;
    uint32_t m_fragmentId;
};

}

#endif

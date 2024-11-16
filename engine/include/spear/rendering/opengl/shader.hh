#ifndef SPEAR_RENDERING_OPENGL_SHADER_HH
#define SPEAR_RENDERING_OPENGL_SHADER_HH

#include <spear/rendering/base_shader.hh>

namespace spear::rendering::opengl
{

class Shader : public BaseShader
{
public:
    /// Constructor.
    Shader(const std::string& vertex_path, const std::string& fragment_path);

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

	/// \param vertex Vertex shaderprogram id.
	/// \param frag Fragment shaderprogram id.
	uint32_t createShaderProgram(int vertex, int frag) override;

private:
	std::string m_vertexCode;
	std::string m_fragmentCode;
};

}

#endif

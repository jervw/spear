#ifndef SPEAR_RENDERING_OPENGL_SHADER_HH
#define SPEAR_RENDERING_OPENGL_SHADER_HH

#include <spear/rendering/shader.hh>

#include <string>

namespace spear::rendering
{

class OpenGLShader : public Shader
{
public:
	/// Constructor.
    OpenGLShader(const std::string& vertex_path, const std::string& fragment_path);

    /// Destructor.
	~OpenGLShader();

    /// Move constructor.
    OpenGLShader(OpenGLShader&& other);

    /// Move assignment operator.
    OpenGLShader& operator=(OpenGLShader&& other);

    /// Deleted copy constructor.
    OpenGLShader(const OpenGLShader&) = delete;

    /// Deleted copy assignment operator.
    Shader& operator=(const OpenGLShader&) = delete;

	/// \param vertex Vertex shaderprogram id.
	/// \param frag Fragment shaderprogram id.
	uint32_t createShaderProgram(int vertex, int frag) override;

private:
	std::string m_vertexCode;
	std::string m_fragmentCode;
};

}

#endif
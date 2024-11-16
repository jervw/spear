#include <spear/rendering/opengl/shader.hh>

#include <GL/glew.h>

#include <fstream>
#include <sstream>

namespace spear::rendering::opengl
{

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path)
{
	// Retrieve the vertex/fragment source code from file path.
	std::ifstream v_shader_file;
	std::ifstream f_shader_file;

	v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open files.
		v_shader_file.open(vertex_path);
		f_shader_file.open(fragment_path);
		std::stringstream vShaderStream, fShaderStream;

		// Read file's buffer contents into streams.
		vShaderStream << v_shader_file.rdbuf();
		fShaderStream << f_shader_file.rdbuf();

		// Close file handlers.
		v_shader_file.close();
		f_shader_file.close();

		// Convert into string.
		m_vertexCode = vShaderStream.str();
		m_fragmentCode = fShaderStream.str();
	}
	catch (const std::ifstream::failure& e)
	{
		printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
	}

	// Compile shaders.
	const char* vShaderCode = m_vertexCode.c_str();
	const char* fShaderCode = m_fragmentCode.c_str();
	int vertex, fragment;

	// Vertex shader.
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	// Fragment shader.
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	setId(createShaderProgram(vertex, fragment));

	// Delete the shaders.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
}

Shader::Shader(Shader&& other)
	: BaseShader(std::move(other)),
	  m_vertexCode(std::move(other.m_vertexCode)),
	  m_fragmentCode(std::move(other.m_fragmentCode))
{
}

Shader& Shader::operator=(Shader&& other)
{
	if (this != &other)
	{
		BaseShader::operator=(std::move(other));
		m_vertexCode = std::move(other.m_vertexCode);
		m_fragmentCode = std::move(other.m_fragmentCode);
	}
	return *this;
}

uint32_t Shader::createShaderProgram(int vertex, int frag)
{
	auto program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, frag);
	glLinkProgram(program);
	checkCompileErrors(program, "PROGRAM");
	return program;
}

}
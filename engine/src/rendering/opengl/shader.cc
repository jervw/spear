#include "spear/rendering/base_shader.hh"
#include "spear/rendering/opengl/error.hh"
#include <spear/rendering/opengl/shader.hh>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

namespace spear::rendering::opengl
{

Shader::Shader(ShaderType type)
{
    rendering::opengl::openglError("before opengl shader contructor");
    auto data = getShaderFiles(type, API::OpenGL);

    std::ifstream v_shader_file;
	std::ifstream f_shader_file;

	v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// Open files.
		v_shader_file.open(data.vertex_shader);
		f_shader_file.open(data.fragment_shader);
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

    rendering::opengl::openglError("before compiling shaders");

	// Compile shaders.
	const char* vShaderCode = m_vertexCode.c_str();
	const char* fShaderCode = m_fragmentCode.c_str();

	// Vertex shader.
    m_vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexId, 1, &vShaderCode, nullptr);
	glCompileShader(m_vertexId);
	checkCompileErrors(m_vertexId, "VERTEX");

	// Fragment shader.
	m_fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentId, 1, &fShaderCode, nullptr);
	glCompileShader(m_fragmentId);
	checkCompileErrors(m_fragmentId, "FRAGMENT");

    rendering::opengl::openglError("after compiling shaders");

    createShaderProgram();

	// Delete the shaders.
	glDeleteShader(m_vertexId);
	glDeleteShader(m_fragmentId);

    rendering::opengl::openglError("opengl shader contructor");
}

Shader::~Shader()
{
}

Shader::Shader(Shader&& other)
	: BaseShader(std::move(other)),
	  m_vertexCode(std::move(other.m_vertexCode)),
	  m_fragmentCode(std::move(other.m_fragmentCode)),
      m_vertexId(std::move(other.m_vertexId)),
      m_fragmentId(std::move(other.m_fragmentId))
{
}

Shader& Shader::operator=(Shader&& other)
{
	if (this != &other)
	{
		BaseShader::operator=(std::move(other));
		m_vertexCode = std::move(other.m_vertexCode);
		m_fragmentCode = std::move(other.m_fragmentCode);
        m_vertexId = std::move(other.m_vertexId);
        m_fragmentId = std::move(other.m_fragmentId);
	}
	return *this;
}


void Shader::setMat4(const std::string& name, const glm::mat4& mat)
{
    // Get the uniform location in the shader program
    GLint location = glGetUniformLocation(BaseShader::getId(), name.c_str());

    if (location == -1)
    {
        std::cerr << "Warning: Uniform '" << name << "' not found in shader program." << std::endl;
        return;
    }

    // Pass the matrix to the shader
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::use()
{
    if (BaseShader::getId() == 0)
    {
        std::cerr << "Error: Shader program is not initialized." << std::endl;
        return;
    }
    glUseProgram(BaseShader::getId());
}

void Shader::createShaderProgram()
{
    GLuint program = glCreateProgram();
    glAttachShader(program, m_vertexId);
    glAttachShader(program, m_fragmentId);
    glLinkProgram(program);

    // Check for linking errors
    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE)
    {
        GLchar log[1024];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        std::cerr << "Shader program linking failed: " << log << std::endl;
        glDeleteProgram(program);
    }
    glUseProgram(program);
    BaseShader::setId(program);
}

}

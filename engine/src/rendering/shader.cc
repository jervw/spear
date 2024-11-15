#include <spear/rendering/shader.hh>

#include <GL/glew.h>

namespace spear::rendering
{

Shader::Shader(Shader&& other)
    : m_id(std::move(other.m_id))
{
}

Shader& Shader::operator=(Shader&& other)
{
    if (this != &other)
    {
        m_id = std::move(other.m_id);
    }
    return *this;
}

void Shader::checkCompileErrors(uint32_t shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			printf("ERROR::SHADER::COMPILATION_ERROR of type: %s\n", infoLog);
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
				printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n", infoLog);
			}
		}
	}
}

Shader::~Shader()
{

}

}


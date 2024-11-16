#include <spear/rendering/base_shader.hh>

#include <GL/glew.h>

namespace spear::rendering
{

BaseShader::BaseShader(BaseShader&& other)
    : m_id(std::move(other.m_id))
{
}

BaseShader& BaseShader::operator=(BaseShader&& other)
{
    if (this != &other)
    {
        m_id = std::move(other.m_id);
    }
    return *this;
}

void BaseShader::checkCompileErrors(uint32_t shader, std::string type)
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

BaseShader::~BaseShader()
{
	// TODO
}

}


#ifndef SPEAR_MATERIAL_HH
#define SPEAR_MATERIAL_HH

#include <spear/rendering/opengl/opengl_shader.hh>
#include <spear/texture.hh>

#include <memory>

namespace spear
{

class Material
{
public:
    /// Constructor.
	Material(std::shared_ptr<rendering::OpenGLShader> shader, Texture&& texture);

	uint32_t getProgram() { return m_shader->getId(); }
	const uint32_t& getMvp() { return m_mvp; } 
	const uint32_t& getColor() const;

	void use();
private:
    std::unique_ptr<rendering::Shader> m_shader;
	Texture m_texture;
	uint32_t m_mvp;
	uint32_t m_color;
};

}

#endif
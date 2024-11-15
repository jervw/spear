#ifndef SPEAR_RENDERING_SHADER_TYPE_HH
#define SPEAR_RENDERING_SHADER_TYPE_HH

#include <spear/rendering/shader.hh>

#include <unordered_map>

namespace spear::rendering
{

enum class ShaderType
{
    basic,
    lightning
};

using shaderCollection = std::unordered_map<ShaderType, Shader>;

}

#endif
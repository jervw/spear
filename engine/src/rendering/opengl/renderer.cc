#include <spear/rendering/opengl/renderer.hh>

#include <iostream>

namespace spear::rendering::opengl
{

Renderer::Renderer(SDL_Window* window)
    : m_window(window)
{
    initGlew();
}

Renderer::~Renderer()
{
}

void Renderer::initGlew()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "GLEW initialization error: " << glewGetErrorString(err) << std::endl;
    }
}

void Renderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setBackgroundColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

}
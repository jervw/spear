#include <spear/rendering/opengl/opengl_renderer.hh>

#include <iostream>

namespace spear::rendering
{

OpenGLRenderer::OpenGLRenderer(SDL_Window* window)
    : m_window(window)
{
    initGlew();
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::initGlew()
{
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "GLEW initialization error: " << glewGetErrorString(err) << std::endl;
    }
}

void OpenGLRenderer::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::setBackgroundColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

}
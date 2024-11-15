#ifndef SPEAR_RENDERING_RENDERER_HH
#define SPEAR_RENDERING_RENDERER_HH

#include <GL/glew.h>
#include <SDL3/SDL.h>

namespace spear::rendering
{

class OpenGLRenderer
{
public:
    /// Constructor.
    OpenGLRenderer(SDL_Window* window);

    // Destructor.
    ~OpenGLRenderer();

    void render();
    void setViewPort(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void setBackgroundColor(float r, float g, float b, float a);

private:
    void initGlew();

private:
    SDL_Window* m_window;
    uint32_t m_shader_program;
};

}

#endif

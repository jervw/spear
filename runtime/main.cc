#include <spear/window.hh>
#include <spear/event_handler.hh>

#include <spear/rendering/opengl/opengl_renderer.hh>
#include <spear/rendering/opengl/opengl_shader.hh>

#include <SDL3/SDL_events.h>

#include <iostream>

int main()
{
    std::string window_name = "Spear application";
    spear::Window::Size window_size = { 820, 640 };
    spear::rendering::API gl_api = spear::rendering::API::OpenGL;

    spear::Window window(window_name, window_size, gl_api);
    //spear::rendering::OpenGLShader basicShader("../shaders/basic_vertex.glsl", "../shaders/basic_fragment.glsl");
    spear::rendering::OpenGLRenderer renderer(window.getSDLWindow());

    renderer.setViewPort(800, 600);
    renderer.setBackgroundColor(0.2f, 0.3f, 0.4f, 1.0f);

    spear::EventHandler eventHandler;

    eventHandler.registerCallback(SDL_EVENT_KEY_DOWN, [](const SDL_Event& event) {
        std::cout << "Key pressed: " << SDL_GetKeyName(event.key.key) << std::endl;
    });

    eventHandler.registerCallback(SDL_EVENT_MOUSE_BUTTON_DOWN, [](const SDL_Event& event) {
        std::cout << "Mouse button pressed at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
    });

    eventHandler.registerCallback(SDL_EVENT_QUIT, [&](const SDL_Event&) {
        std::cout << "Quit event received. Exiting..." << std::endl;
        exit(0);
    });

    while (true)
    {
        eventHandler.handleEvents();
        renderer.render();
        window.update(gl_api);
    }
    /*
    // Contains Camera, input,
    spear::Player;

    spear::Scene scene;
    scene.addItems<spear::object>(person, cube);

    */

}

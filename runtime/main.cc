#include <spear/window.hh>
#include <spear/event_handler.hh>
#include <spear/shapes/cube.hh>
#include <spear/camera.hh>

#include <spear/rendering/opengl/shader.hh>
#include <spear/rendering/opengl/renderer.hh>
#include <spear/rendering/opengl/texture.hh>

#include <SDL3/SDL_events.h>

#include <iostream>

int main()
{
    std::string window_name = "Spear application";
    spear::Window::Size window_size = { 820, 640 };
    spear::rendering::API gl_api = spear::rendering::API::OpenGL;

    spear::Window window(window_name, window_size, gl_api);
    //spear::rendering::opengl::Shader basicShader("../shaders/basic_vertex.glsl", "../shaders/basic_fragment.glsl");
    spear::rendering::opengl::Renderer renderer(window.getSDLWindow());

    renderer.setViewPort(800, 600);
    renderer.setBackgroundColor(0.2f, 0.3f, 0.4f, 1.0f);

    spear::Camera camera;
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

    //spear::rendering::opengl::Texture tex;
    //tex.loadFromFile("../engine/assets/niilo.jpg");

    while (true)
    {
        eventHandler.handleEvents();
        renderer.render();
        window.update(gl_api);
    }
}

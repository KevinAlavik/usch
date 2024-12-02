#include "engine.hpp"

namespace Engine
{

    Window::Window(const std::string &title, const math::Vec2 &size)
        : window_(nullptr)
    {
        window_ = SDL_CreateWindow(
            title.c_str(),
            static_cast<int>(size.x),
            static_cast<int>(size.y),
            0);

        if (!window_)
        {
            throw std::runtime_error("Failed to create SDL_Window: " + std::string(SDL_GetError()));
        }
    }

    Window::~Window()
    {
        if (window_)
        {
            SDL_DestroyWindow(window_);
        }
    }

    Renderer::Renderer(const Window &window)
        : renderer_(nullptr)
    {
        renderer_ = SDL_CreateRenderer(window.getHandle(), nullptr);
        if (!renderer_)
        {
            throw std::runtime_error("Failed to create SDL_Renderer: " + std::string(SDL_GetError()));
        }
    }

    Renderer::~Renderer()
    {
        if (renderer_)
        {
            SDL_DestroyRenderer(renderer_);
        }
    }

    void Renderer::setDrawColor(math::Vec4 color)
    {
        Uint8 r = static_cast<Uint8>(std::clamp(color.x * 255.0f, 0.0f, 255.0f));
        Uint8 g = static_cast<Uint8>(std::clamp(color.y * 255.0f, 0.0f, 255.0f));
        Uint8 b = static_cast<Uint8>(std::clamp(color.z * 255.0f, 0.0f, 255.0f));
        Uint8 a = static_cast<Uint8>(std::clamp(color.w * 255.0f, 0.0f, 255.0f));

        if (!SDL_SetRenderDrawColor(renderer_, r, g, b, a))
        {
            throw std::runtime_error("Failed to set render draw color: " + std::string(SDL_GetError()));
        }
    }

    void Renderer::clear()
    {
        if (!SDL_RenderClear(renderer_))
        {
            throw std::runtime_error("Failed to clear renderer: " + std::string(SDL_GetError()));
        }
    }

    void Renderer::present()
    {
        SDL_RenderPresent(renderer_);
    }

}

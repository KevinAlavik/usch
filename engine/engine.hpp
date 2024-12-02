#pragma once

#include <SDL3/SDL.h>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "../math/vector.hpp"

namespace Engine
{

    class Renderer;

    class Window
    {
    public:
        Window(const std::string &title, const math::Vec2 &size);
        ~Window();

        SDL_Window *getHandle() const { return window_; }

    private:
        SDL_Window *window_;
        friend class Renderer;
    };

    class Renderer
    {
    public:
        Renderer(const Window &window);
        ~Renderer();

        void setDrawColor(math::Vec4 color);
        void clear();
        void present();

        SDL_Renderer *getHandle() const { return renderer_; }

    private:
        SDL_Renderer *renderer_;
    };

}

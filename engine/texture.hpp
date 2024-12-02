#pragma once

#include "engine.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <stdexcept>

namespace Engine
{
    class Texture
    {
    public:
        Texture(SDL_Renderer *renderer, const std::string &filePath);
        ~Texture();

        SDL_Texture *getHandle() const;
        int getWidth() const;
        int getHeight() const;

    private:
        SDL_Renderer *renderer_;
        SDL_Texture *texture_;
        int width_;
        int height_;

        void loadFromFile(const std::string &filePath);
    };
}

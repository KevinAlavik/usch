#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <stdexcept>

namespace Engine
{
    class Renderer;

    class Texture
    {
    public:
        Texture(Renderer &renderer, const std::string &filePath);
        ~Texture();

        SDL_Texture *getHandle() const;
        SDL_FRect getSrcRect() const;

        void setPosition(float x, float y);
        void setScale(float scaleX, float scaleY);
        void setRotation(float angle);
        void setFlip(SDL_FlipMode flip);

        float getRotation() const { return rotation_; }
        SDL_FlipMode getFlip() const { return flip_; }

        void applyTransformations(SDL_FRect &destRect);

    private:
        Renderer &renderer_;
        SDL_Texture *texture_;
        float x_, y_;
        float scaleX_, scaleY_;
        float rotation_;
        SDL_FlipMode flip_;
    };
}

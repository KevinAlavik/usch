#include "texture.hpp"
#include "engine.hpp"
#include <SDL3_image/SDL_image.h>

namespace Engine
{
    Texture::Texture(Renderer &renderer, const std::string &filePath)
        : renderer_(renderer), texture_(nullptr), x_(0), y_(0), scaleX_(1.0f), scaleY_(1.0f), rotation_(0.0f), flip_(SDL_FLIP_NONE)
    {
        SDL_Surface *surface = IMG_Load(filePath.c_str());
        if (!surface)
        {
            throw std::runtime_error("Failed to load image: " + std::string(SDL_GetError()));
        }

        texture_ = SDL_CreateTextureFromSurface(renderer_.getHandle(), surface);
        SDL_DestroySurface(surface);

        if (!texture_)
        {
            throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
        }
    }

    Texture::~Texture()
    {
        if (texture_)
        {
            SDL_DestroyTexture(texture_);
        }
    }

    SDL_Texture *Texture::getHandle() const
    {
        return texture_;
    }

    SDL_FRect Texture::getSrcRect() const
    {
        float width, height;
        SDL_GetTextureSize(texture_, &width, &height);
        return SDL_FRect{0, 0, width, height};
    }

    void Texture::setPosition(float x, float y)
    {
        x_ = x;
        y_ = y;
    }

    void Texture::setScale(float scaleX, float scaleY)
    {
        scaleX_ = scaleX;
        scaleY_ = scaleY;
    }

    void Texture::setRotation(float angle)
    {
        rotation_ = angle;
    }

    void Texture::setFlip(SDL_FlipMode flip)
    {
        flip_ = flip;
    }

    void Texture::applyTransformations(SDL_FRect &destRect)
    {
        destRect.w *= scaleX_;
        destRect.h *= scaleY_;
    }
}
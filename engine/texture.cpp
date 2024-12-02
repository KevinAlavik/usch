#include "texture.hpp"
#include <SDL3_image/SDL_image.h>

namespace Engine
{
    Texture::Texture(SDL_Renderer *renderer, const std::string &filePath)
        : renderer_(renderer), texture_(nullptr), width_(0), height_(0)
    {
        if (!renderer_)
        {
            throw std::invalid_argument("Renderer cannot be null.");
        }

        loadFromFile(filePath);
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

    int Texture::getWidth() const
    {
        return width_;
    }

    int Texture::getHeight() const
    {
        return height_;
    }

    void Texture::loadFromFile(const std::string &filePath)
    {
        SDL_Surface *surface = IMG_Load(filePath.c_str());
        if (!surface)
        {
            throw std::runtime_error("Failed to load image: " + std::string(SDL_GetError()));
        }

        texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
        if (!texture_)
        {
            SDL_DestroySurface(surface);
            throw std::runtime_error("Failed to create texture: " + std::string(SDL_GetError()));
        }

        width_ = surface->w;
        height_ = surface->h;

        SDL_DestroySurface(surface);
    }
}

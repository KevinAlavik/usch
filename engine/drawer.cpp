#include "drawer.hpp"
#include <cmath>

namespace Engine
{
    Drawer::Drawer(Renderer &renderer) : renderer_(renderer) {}

    void Drawer::setColor(const math::Vec4 &color)
    {
        renderer_.setDrawColor(color);
    }

    void Drawer::drawLine(const math::Vec2 &start, const math::Vec2 &end)
    {
        if (!SDL_RenderLine(renderer_.getHandle(), static_cast<int>(start.x), static_cast<int>(start.y),
                            static_cast<int>(end.x), static_cast<int>(end.y)))
        {
            throw std::runtime_error("Failed to draw line: " + std::string(SDL_GetError()));
        }
    }

    void Drawer::drawRect(const math::Vec2 &position, const math::Vec2 &size, bool filled)
    {
        SDL_FRect rect = {position.x, position.y, size.x, size.y};
        if (filled)
        {
            if (!SDL_RenderFillRect(renderer_.getHandle(), &rect))
            {
                throw std::runtime_error("Failed to draw filled rectangle: " + std::string(SDL_GetError()));
            }
        }
        else
        {
            if (!SDL_RenderRect(renderer_.getHandle(), &rect))
            {
                throw std::runtime_error("Failed to draw rectangle: " + std::string(SDL_GetError()));
            }
        }
    }

    void Drawer::drawCircle(const math::Vec2 &center, float radius, bool filled)
    {
        const int diameter = (radius * 2);

        int x = (radius - 1);
        int y = 0;
        int tx = 1;
        int ty = 1;
        int error = (tx - diameter);

        while (x >= y)
        {
            SDL_RenderPoint(renderer_.getHandle(), center.x + x, center.y - y);
            SDL_RenderPoint(renderer_.getHandle(), center.x + x, center.y + y);
            SDL_RenderPoint(renderer_.getHandle(), center.x - x, center.y - y);
            SDL_RenderPoint(renderer_.getHandle(), center.x - x, center.y + y);
            SDL_RenderPoint(renderer_.getHandle(), center.x + y, center.y - x);
            SDL_RenderPoint(renderer_.getHandle(), center.x + y, center.y + x);
            SDL_RenderPoint(renderer_.getHandle(), center.x - y, center.y - x);
            SDL_RenderPoint(renderer_.getHandle(), center.x - y, center.y + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
    }

    void Drawer::drawTexture(const math::Vec2 &position, Texture &texture)
    {
        SDL_FRect sourceRect = texture.getSrcRect();
        SDL_FRect destRect = {position.x, position.y, static_cast<float>(sourceRect.w), static_cast<float>(sourceRect.h)};

        texture.applyTransformations(destRect);

        if (!SDL_RenderTextureRotated(renderer_.getHandle(), texture.getHandle(), &sourceRect, &destRect, texture.getRotation(), nullptr, texture.getFlip()))
        {
            throw std::runtime_error("Failed to draw texture: " + std::string(SDL_GetError()));
        }
    }
}

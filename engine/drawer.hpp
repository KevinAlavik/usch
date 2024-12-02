#pragma once

#include "engine.hpp"
#include "texture.hpp"
#include "../math/vector.hpp"
#include <SDL3/SDL.h>

namespace Engine
{
    class Drawer
    {
    public:
        Drawer(Renderer &renderer);
        ~Drawer() = default;

        void setColor(const math::Vec4 &color);
        void drawLine(const math::Vec2 &start, const math::Vec2 &end);
        void drawRect(const math::Vec2 &position, const math::Vec2 &size, bool filled = false);
        void drawCircle(const math::Vec2 &center, float radius, bool filled = false);
        void drawTexture(const math::Vec2 &position, const Texture &texture);

    private:
        Renderer &renderer_;
    };
}

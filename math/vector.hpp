#pragma once

#include <cmath>
#include <iostream>
#include <algorithm>

namespace math
{

    class Vec2
    {
    public:
        float x, y;

        Vec2() : x(0), y(0) {}
        Vec2(float x, float y) : x(x), y(y) {}

        Vec2 operator+(const Vec2 &other) const
        {
            return Vec2(x + other.x, y + other.y);
        }

        Vec2 operator-(const Vec2 &other) const
        {
            return Vec2(x - other.x, y - other.y);
        }

        float dot(const Vec2 &other) const
        {
            return x * other.x + y * other.y;
        }

        float length() const
        {
            return std::sqrt(x * x + y * y);
        }

        Vec2 normalize() const
        {
            float len = length();
            return len != 0 ? Vec2(x / len, y / len) : Vec2(0, 0);
        }

        Vec2 clamp(float minVal, float maxVal) const
        {
            return Vec2(
                std::clamp(x, minVal, maxVal),
                std::clamp(y, minVal, maxVal));
        }

        friend std::ostream &operator<<(std::ostream &os, const Vec2 &v)
        {
            os << "(" << v.x << ", " << v.y << ")";
            return os;
        }
    };

    class Vec3
    {
    public:
        float x, y, z;

        Vec3() : x(0), y(0), z(0) {}
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        Vec3 operator+(const Vec3 &other) const
        {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }

        Vec3 operator-(const Vec3 &other) const
        {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }

        float dot(const Vec3 &other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        Vec3 cross(const Vec3 &other) const
        {
            return Vec3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
        }

        float length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        Vec3 normalize() const
        {
            float len = length();
            return len != 0 ? Vec3(x / len, y / len, z / len) : Vec3(0, 0, 0);
        }

        Vec3 clamp(float minVal, float maxVal) const
        {
            return Vec3(
                std::clamp(x, minVal, maxVal),
                std::clamp(y, minVal, maxVal),
                std::clamp(z, minVal, maxVal));
        }

        friend std::ostream &operator<<(std::ostream &os, const Vec3 &v)
        {
            os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
            return os;
        }
    };

    class Vec4
    {
    public:
        float x, y, z, w;

        Vec4() : x(0), y(0), z(0), w(0) {}
        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        Vec4 operator+(const Vec4 &other) const
        {
            return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        Vec4 operator-(const Vec4 &other) const
        {
            return Vec4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        float dot(const Vec4 &other) const
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        float length() const
        {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        Vec4 normalize() const
        {
            float len = length();
            return len != 0 ? Vec4(x / len, y / len, z / len, w / len) : Vec4(0, 0, 0, 0);
        }

        Vec4 clamp(float minVal, float maxVal) const
        {
            return Vec4(
                std::clamp(x, minVal, maxVal),
                std::clamp(y, minVal, maxVal),
                std::clamp(z, minVal, maxVal),
                std::clamp(w, minVal, maxVal));
        }

        friend std::ostream &operator<<(std::ostream &os, const Vec4 &v)
        {
            os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
            return os;
        }
    };

}

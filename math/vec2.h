#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    struct vec<2, T>
    {
        typedef vec<2, T> type;
        T x, y;

        vec() : x(0), y(0) {}
        vec(T scalar) : x(scalar), y(scalar) {}
        vec(T x, T y) : x(x), y(y) {}

        type operator+(const type& other) const
        {
            return type(x + other.x, y + other.y);
        }

        type operator-(const type& other) const
        {
            return type(x - other.x, y - other.y);
        }

        T operator*(const type& other) const
        {
            return x * other.x + y * other.y;
        }

        type operator*(T scalar) const
        {
            return type(x * scalar, y * scalar);
        }

        friend type operator*(T scalar, const type& v)
        {
            return type(v.x * scalar, v.y * scalar);
        }

        friend std::ostream& operator<<(std::ostream& os, const type& vec)
        {
            return os << "vec2(" << vec.x << ", " << vec.y << ")";
        }
    };
}
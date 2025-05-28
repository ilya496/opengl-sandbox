#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    class vec<2, T>
    {
        typedef vec<2, T> type;

    public:
        vec() : x(0), y(0) {}
        vec(const type& v) : x(v.x), y(v.y) {}
        vec(T scalar) : x(scalar), y(scalar) {}
        vec(T _x, T _y) : x(_x), y(_y) {}

    public:
        T x, y;

        T& operator[](int i)
        {
            switch (i)
            {
            default:
            case 0:
                return x;
            case 1:
                return y;
            }
        }

        const T& operator[](int i) const
        {
            switch (i)
            {
            default:
            case 0:
                return x;
            case 1:
                return y;
            }
        }

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
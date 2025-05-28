#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    class vec<4, T> {
        typedef vec<4, T> type;

    public:
        vec() : x(0), y(0), z(0), w(0) {}
        vec(const type& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
        vec(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
        vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

    public:
        T x, y, z, w;

        T& operator[](int i)
        {
            switch (i)
            {
            default:
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return x;
            case 3:
                return w;
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
            case 2:
                return z;
            case 3:
                return w;
            }
        }

        T operator*(const type& other) const
        {
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        friend std::ostream& operator<<(std::ostream& os, const type& vec)
        {
            return os << "vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
        }
    };
}
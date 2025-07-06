#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    class vec<3, T> {
        typedef vec<3, T> type;
    
    public:
        vec() : x(0), y(0), z(0) {}
        vec(const type& v) : x(v.x), y(v.y), z(v.z) {}
        vec(T scalar) : x(scalar), y(scalar), z(scalar) {}
        vec(T x, T y, T z) : x(x), y(y), z(z) {}

    public:
        T x, y, z;

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
            }
        }

        type operator+(const type& other) const
        {
            return type(x + other.x, y + other.y, z + other.z);
        }

        type operator-(const type& other) const
        {
            return type(x - other.x, y - other.y, z - other.z);
        }

        T operator*(const type& other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        type operator*(T scalar) const
        {
            return type(x * scalar, y * scalar, z * scalar);
        }

        type& operator+=(const type& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        type& operator-=(const type& other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        friend type operator*(T scalar, const type& v)
        {
            return type(v.x * scalar, v.y * scalar, v.z * scalar);
        }

        friend std::ostream& operator<<(std::ostream& os, const type& vec)
        {
            return os << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        }
    };
}
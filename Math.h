#pragma once

#ifndef M_PI
#define M_PI 3.141592
#endif

#include <cmath>
#include <ostream>

namespace math 
{

	inline float toRad(float degrees) { return degrees * (M_PI / 180.0f); }
	inline float toDeg(float radians) { return radians * (180.0f / M_PI); }

	template<size_t L, typename T> struct vec;

	template<typename T>
	struct vec<2, T>
	{
		using self = vec<2, T>;
		T x, y;

		vec() : x(0), y(0) {}
		vec(T scalar) : x(scalar), y(scalar) {}
		vec(T x, T y) : x(x), y(y) {}

		self operator+(const self& other) const 
		{
			return self(x + other.x, y + other.y);
		}

		self operator-(const self& other) const 
		{
			return self(x - other.x, y - other.y);
		}

		self operator*(const self& other) const 
		{
			return self(x * other.x, y * other.y);
		}

		self operator/(const self& other) const 
		{
			return self(x / other.x, y / other.y);
		}

		self operator*(T scalar) const 
		{
			return self(x * scalar, y * scalar);
		}

		self& operator+=(const self& other) 
		{
			x += other.x; y += other.y;
			return *this;
		}

		self& operator-=(const self& other) 
		{
			x -= other.x; y -= other.y;
			return *this;
		}

		self& operator*=(T scalar) 
		{
			x *= scalar; y *= scalar;
			return *this;
		}

		friend self operator*(T scalar, const self& v) 
		{
			return self(v.x * scalar, v.y * scalar);
		}

		friend std::ostream& operator<<(std::ostream& os, const self& vec) 
		{
			return os << "vec2(" << vec.x << ", " << vec.y << ")";
		}
	};

	template<typename T>
	struct vec<3, T> {
		T x, y, z;

		vec() : x(0), y(0), z(0) {}
		vec(T scalar) : x(scalar), y(scalar), z(scalar) {}
		vec(T x, T y, T z) : x(x), y(y), z(z) {}
	};

	template<typename T>
	struct vec<4, T> {
		T x, y, z, w;

		vec() : x(0), y(0), z(0), w(0) {}
		vec(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
		vec(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	};

	using vec2 = vec<2, float>;
	using vec3 = vec<3, float>;
	using vec4 = vec<4, float>;
	using ivec2 = vec<2, int>;
	using ivec3 = vec<3, int>;
	using ivec4 = vec<4, int>;

} // namespace math
#pragma once

#ifndef M_PI
#define M_PI 3.141592
#endif

#include <cmath>

namespace math {

	inline float toRad(float degrees) { return degrees * (M_PI / 180.0f); }
	inline float toDeg(float radians) { return radians * (180.0f / M_PI); }

	template<size_t L, typename T> struct vec;

	template<typename T>
	struct vec<2, T> {
		T x, y;
		// TODO: learn how to use union
		//union { T x, r, s };
		//union { T y, g, t };
		//union { T z, b, p };
		//union { T w, a, q };
	};

	template<typename T> using vec2 = vec<2, T>;
	template<typename T> using vec3 = vec<3, T>;
	template<typename T> using vec4 = vec<4, T>;

} // namespace math
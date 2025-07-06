#pragma once

#include <cmath>
#include <ostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace math
{
	template<int L, typename T> struct vec;
	template<int R, int C, typename T> struct mat;

	typedef vec<2, float> vec2;
	typedef vec<3, float> vec3;
	typedef vec<4, float> vec4;

	typedef vec<2, int> ivec2;
	typedef vec<3, int> ivec3;
	typedef vec<4, int> ivec4;

	typedef mat<2, 2, float> mat2;
	typedef mat<3, 3, float> mat3;
	typedef mat<4, 4, float> mat4;
}
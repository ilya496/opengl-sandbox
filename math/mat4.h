#pragma once

#include "base.h"

namespace math
{
	template<typename T>
	class mat<4, 4, T>
	{
		typedef vec<4, T> row_type;
		typedef vec<4, T> col_type;
		typedef mat<4, 4, T> type;
		typedef mat<4, 4, T> transpose_type;

	public:
        mat() : m_Data{ 
            row_type(1, 0, 0, 0), 
            row_type(0, 1, 0, 0), 
            row_type(0, 0, 1, 0), 
            row_type(0, 0, 0, 1)
        } {}

        mat(const type& m) : m_Data{ 
            row_type(m[0]), row_type(m[1]), 
            row_type(m[2]), row_type(m[3])
        } {}

        mat(T scalar) : m_Data{
            row_type(scalar, 0, 0, 0),
            row_type(0, scalar, 0, 0),
            row_type(0, 0, scalar, 0),
            row_type(0, 0, 0, scalar)
        } {}

        mat(const T& x0, const T& y0, const T& z0, const T& w0,
            const T& x1, const T& y1, const T& z1, const T& w1,
            const T& x2, const T& y2, const T& z2, const T& w2, 
            const T& x3, const T& y3, const T& z3, const T& w3
        ) : m_Data{ 
            row_type(x0, y0, z0, w0), row_type(x1, y1, z1, w1),
            row_type(x2, y2, z2, w2), row_type(x3, y3, z3, w3)
        } {}

        mat(const row_type& v0, const row_type& v1, const row_type& v2, const row_type& v3)
            : m_Data{ v0, v1, v2, v3 } {}

	public:
        row_type& operator[](int i)
        {
            return m_Data[i];
        }

        const row_type& operator[](int i) const
        {
            return m_Data[i];
        }

        friend std::ostream& operator<<(std::ostream& os, const type& mat)
        {
            os << "mat4(\n";
            for (int i = 0; i < 4; ++i)
            {
                os << "  ";
                for (int j = 0; j < 4; ++j)
                {
                    os << mat[i][j] << ", ";
                }
                os << '\n';
            }
            os << ')';

            return os;
        }

	private:
		row_type m_Data[4];
	};
}
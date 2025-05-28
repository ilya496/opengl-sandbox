#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    class mat<2, 2, T>
    {
        typedef vec<2, T> col_type;
        typedef vec<2, T> row_type;
        typedef mat<2, 2, T> type;
        typedef mat<2, 2, T> transpose_type;

    public:
        mat() : m_Data{ row_type(1, 0), row_type(0, 1) } {}

        mat(const type& m) : m_Data{ row_type(m[0]), row_type(m[1]) } {}

        mat(T scalar) : m_Data{ row_type(scalar, 0), row_type(0, scalar) } {}

		mat(const T& x0, const T& y0, const T& x1, const T& y1)
			: m_Data{ row_type(x0, y0), row_type(x1, y1) } {}

		mat(const row_type& v0, const row_type& v1)
            : m_Data{ v0, v1 } {}

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
            os << "mat2(\n";
            for (int i = 0; i < 2; ++i)
            {
                os << "  ";
                for (int j = 0; j < 2; ++j)
                {
                    os << mat[i][j] << ", ";
                }
                os << '\n';
            }
            os << ')';

            return os;
        }

    private:
        row_type m_Data[2];
    };
}
#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    class mat<3, 3, T>
    {
        typedef vec<3, T> col_type;
        typedef vec<3, T> row_type;
        typedef mat<3, 3, T> type;
        typedef mat<3, 3, T> transpose_type;

    public:
        mat() : m_Data{ row_type(1, 0, 0), row_type(0, 1, 0), row_type(0, 0, 1) } {}

        mat(const type& m) : m_Data{ row_type(m[0]), row_type(m[1]), row_type(m[2]) } {}

        mat(T scalar)
            : m_Data{ row_type(scalar, 0, 0), row_type(0, scalar, 0), row_type(0, 0, scalar) } {
        }

        mat(
            const T& x0, const T& y0, const T& z0,
            const T& x1, const T& y1, const T& z1,
            const T& x2, const T& y2, const T& z2
        )
            : m_Data{ row_type(x0, y0, z0), row_type(x1, y1, z1), row_type(x2, y2, z2) } {
        }

        mat(const row_type& v0, const row_type& v1, const row_type& v2)
            : m_Data{ v0, v1, v2 } {
        }

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
            os << "mat3(\n";
            for (int i = 0; i < 3; ++i)
            {
                os << "  ";
                for (int j = 0; j < 3; ++j)
                {
                    os << mat[i][j] << ", ";
                }
                os << '\n';
            }
            os << ')';

            return os;
        }

    private:
        row_type m_Data[3];
    };
}
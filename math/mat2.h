#pragma once

#include "base.h"

namespace math
{
    template<typename T>
    struct mat<2, 2, T>
    {
        typedef vec<2, T> col_type;
        typedef vec<2, T> row_type;
        typedef mat<2, 2, T> type;
        // typedef mat<2, 2, T> transpose_type;

    public:
        mat();
        mat(const type& m);
        mat(T scalar);
        mat(const T& x1, const T& y1, const T& x2, const T& y2);
        mat(col_type const& v1, col_type const& v2);

    public:
        static constexpr int length() { return 2; }

        col_type& operator[](int i);
        const col_type& operator[](int i) const;

    private:
        col_type value[2];
    };
}
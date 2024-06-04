#if !defined(MATRIX_H)
#define MATRIX_H

#include <vector>
#include "matrix_impl.h"

template<typename T, size_t N>
using Matrix_Initializer = typename Matrix_Impl::Matrix_Init<T,N>::type;

template<typename T, size_t N>
class matrix{

    std::vector<T> data;

    public:
        matrix()=default;

        matrix(matrix&&)=default;
        matrix& operator=(matrix&&)=default;

        matrix(const matrix&)=default;
        matrix& operator=(const matrix&)=default;
        template<typename U>
        matrix(std::initializer_list<U>)=delete;
        template<typename U>
        matrix& operator=(std::initializer_list<U>)=delete;

        matrix(Matrix_Initializer<T,N>);
        matrix& operator=(Matrix_Initializer<T,N>);
};



#endif // MATRIX_H

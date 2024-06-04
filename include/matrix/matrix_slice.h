#if !defined(MATRIX_SLICE)
#define MATRIX_SLICE
#include <initializer_list>
#include <array>

template<size_t N>
struct Matrix_slice{
    Matrix_slice() = default;

    size_t size;
    size_t start;
    std::array<size_t,N> extents;
    std::array<size_t,N> strides;

    Matrix_slice(size_t s, std::initializer_list<size_t> exts);
    Matrix_slice(size_t s, std::initializer_list<size_t> exts, std::initializer_list<size_t> strs);
};

template<size_t N>
Matrix_slice<N>::Matrix_slice(size_t s, std::initializer_list<size_t> exts)
    : size{1}, start{s}
{
    size_t i = 0;
    for(auto x : exts){
        extents[i] = x;
        size *= x;
        ++i;
    }

    for (size_t i = 0; i < N; i++)
    {
        if(i==0)
        {
            strides[i] = 1;
        }else{
            strides[i] = strides[i-1] * extents[i-1];
        }
    }
    
   
};

template<size_t N>
Matrix_slice<N>::Matrix_slice(size_t s, std::initializer_list<size_t> exts, std::initializer_list<size_t> strs)
    : size{1}, start{s}
{
    size_t i = 0;
    for(auto x : exts){
        extents[i] = x;
        size *= x;
        ++i;
    }
    i = 0;
    for(auto x : strs){
        strides[i] = x;
        ++i;
    }
};
#endif // MATRIX_SLICE

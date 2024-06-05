#if !defined(MATRIX_SLICE)
#define MATRIX_SLICE
#include <initializer_list>
#include <array>

template<size_t N>
struct Matrix_slice{
    Matrix_slice();
    ~Matrix_slice() = default;

    size_t size;
    size_t start;
    std::array<size_t,N> extents;
    std::array<size_t,N> strides;

    Matrix_slice(size_t s, std::initializer_list<size_t> exts);
    Matrix_slice(size_t s, std::initializer_list<size_t> exts, std::initializer_list<size_t> strs);
    template<typename... Dims>
    Matrix_slice(Dims... dims);


    template<typename... Dims,
             typename RT= std::enable_if<std::conjunction<std::is_convertible<Dims,size_t>...>::value>::type>
    std::size_t operator()(Dims... dims)const;
 
};
template<size_t N>
Matrix_slice<N>::Matrix_slice()
    : size{0}, start{0}
{
    extents.fill(0);
    strides.fill(0);
};

template<size_t N>
Matrix_slice<N>::Matrix_slice(size_t s, std::initializer_list<size_t> exts)
    : size{1}, start{s}
{
    size_t i = 0;
    strides[i]=1;
    for(auto x : exts){
        extents[i] = x;
        size *= x;
        ++i;
    }

    for (size_t i = 1; i < N; i++)
    {
        strides[i] = strides[i-1] * extents[N-i];
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

template<size_t N>
template<typename... Dims>
Matrix_slice<N>::Matrix_slice(Dims... dims)
    : size{1}, start{0}
{
    static_assert(sizeof...(Dims) == N, "Number of dimensions must match");
    size_t i = 0;
    strides[i]=1;
    for(auto x : {dims...}){
        extents[i] = x;
        size *= x;
        ++i;
    }

  for (size_t i = 1; i < N; i++)
    {
        strides[i] = strides[i-1] * extents[N-i];
    }
    
};

template<size_t N>
template<typename... Dims, typename RT>
std::size_t Matrix_slice<N>::operator()(Dims... dims)const
{
    static_assert(sizeof...(Dims) == N, "Number of dimensions must match");
    size_t args[] = {static_cast<size_t>(dims)...};
    size_t res = start;
    for (size_t i = 0; i < N; i++)
    {
        res += args[i] * strides[i];
    }
    return res;
}

#endif // MATRIX_SLICE

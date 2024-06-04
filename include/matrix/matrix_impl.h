
#include <initializer_list> // Add this line
namespace Matrix_Impl
{




    template<typename T, size_t N>
    struct Matrix_Init{
        using type = std::initializer_list<typename Matrix_Init<T, N-1>::type>;
    };

    template<typename T>
    struct Matrix_Init<T,1>
    {
        using type = std::initializer_list<T>;
    };

    template<typename T>
    struct Matrix_Init<T,0>;
    
    
} // namespace Matrix_Impl

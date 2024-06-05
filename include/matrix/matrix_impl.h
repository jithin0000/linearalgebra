
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


    constexpr bool All(){return true;}
    template<typename... Args>
    constexpr bool All(bool b, Args... args)
    {
        return b && All(args...);
    }

    template <typename T, typename U>
    constexpr bool Convertible(T, U)
    {
        return std::is_convertible<T,U>::value;
    }

    template<size_t N>
    void calculate_strides(const std::array<size_t,N>& extents, std::array<size_t,N>& strides)
    {
        strides[N-1] = 1;
        for(size_t i = N-1; i > 0; --i)
            strides[i-1] = strides[i] * extents[i];
    }

    template<size_t N>
    void calculate_size(const std::array<size_t,N>& extents, size_t& size)
    {
        size = 1;
        for(size_t i = 0; i < N; ++i)
            size *= extents[i];
    }

   template<size_t N, typename List>
   void derive_extents(const List& list, std::array<size_t,N>& a)
   {
    auto f = a.begin();
    add_extents<N>(f,list);
   }



   template<size_t N, typename l, typename List>
   std::enable_if_t<(N>1),void> add_extents(l& first, const List& list)
   {
        assert(check_non_jagged(list));
        *first = list.size();
        add_extents<N-1>(++first,*list.begin());
   }

   template<size_t N, typename l, typename List>
   std::enable_if_t<(N==1),void> add_extents(l& first, const List& list)
   {
    *first++ = list.size();
   }

   template<typename List>
   bool check_non_jagged(const List& list)
   {
    auto i = list.begin();
    for(auto j=i+1; j != list.end();++j)
        if(i->size() != j->size())
            return false;
    return true;
   }

    
    
} // namespace Matrix_Impl

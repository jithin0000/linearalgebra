#if !defined(MATRIX_H)
#define MATRIX_H

#include <vector>
#include "matrix_impl.h"
#include "matrix_slice.h"


template<typename T, size_t N>
class matrix{

    std::vector<T> elements;
    Matrix_slice<N> desc;



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

        matrix(Matrix_Impl::Matrix_Initializer<T,N>);
        matrix& operator=(Matrix_Impl::Matrix_Initializer<T,N>);

        template<typename... Exts>
        explicit matrix(Exts... exts);

        static constexpr size_t order(){return N;}
        size_t extent(int i)const{return desc.extents[i];}
        size_t size()const{return elements.size();}

        T* data(){return elements.data;}
        const T* data()const{return elements.data;}

};

template<typename T, size_t N>
template<typename... Exts>
matrix<T,N>::matrix(Exts... exts)
    : desc{exts...}
{
    elements.resize(desc.size);
}

template<typename T, size_t N>
matrix<T,N>::matrix(Matrix_Impl::Matrix_Initializer<T,N> init)
{
    Matrix_Impl::derive_extents<N>(init,desc.extents);
    Matrix_Impl::calculate_strides(desc.extents, desc.strides);
    Matrix_Impl::calculate_size(desc.extents, desc.size);
    elements.reserve(desc.size);
    Matrix_Impl::insert_flat(init,elements);
    assert(elements.size() == desc.size);
}




#endif // MATRIX_H

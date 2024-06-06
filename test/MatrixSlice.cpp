#include <gtest/gtest.h>
#include "matrix/matrix.h"

#include "matrix/matrix_slice.h"

TEST(MATRIX_SLICED, DEFAULT_CONSTRUCT)
{
    Matrix_slice<3> slice;
    EXPECT_EQ(slice.size, 0);
    EXPECT_EQ(slice.start, 0);
    EXPECT_EQ(slice.extents[0], 0);
    EXPECT_EQ(slice.extents[1], 0);
    EXPECT_EQ(slice.extents[2], 0);
    EXPECT_EQ(slice.strides[0], 0);
    EXPECT_EQ(slice.strides[1], 0);
    EXPECT_EQ(slice.strides[2], 0);
}


TEST(MATRIX_SLICED, CONSTRUCT)
{
    Matrix_slice<3> slice(0, {3,3,2});
    EXPECT_EQ(slice.size, 18);
    EXPECT_EQ(slice.start, 0);
    EXPECT_EQ(slice.extents[0], 3);
    EXPECT_EQ(slice.extents[1], 3);
    EXPECT_EQ(slice.extents[2], 2);
    EXPECT_EQ(slice.strides[0], 9);
    EXPECT_EQ(slice.strides[1], 3);
    EXPECT_EQ(slice.strides[2], 1);

}

TEST(MATRIX_SLICED, CONSTRUCT_STRIDES)
{
    Matrix_slice<3> slice(0, {3,3,2}, {1,3,9});
    EXPECT_EQ(slice.size, 18);
    EXPECT_EQ(slice.start, 0);
    EXPECT_EQ(slice.extents[0], 3);
    EXPECT_EQ(slice.extents[1], 3);
    EXPECT_EQ(slice.extents[2], 2);
    EXPECT_EQ(slice.strides[0], 1);
    EXPECT_EQ(slice.strides[1], 3);
    EXPECT_EQ(slice.strides[2], 9);

}

TEST(MATRIX_SLICED, CONSTRUCT_DIMS)
{
    Matrix_slice<3> slice( 3, 3, 2);
    EXPECT_EQ(slice.size, 18);
    EXPECT_EQ(slice.start, 0);
    EXPECT_EQ(slice.extents[0], 3);
    EXPECT_EQ(slice.extents[1], 3);
    EXPECT_EQ(slice.extents[2], 2);
    EXPECT_EQ(slice.strides[0], 9);
    EXPECT_EQ(slice.strides[1], 3);
    EXPECT_EQ(slice.strides[2], 1);
}

TEST(MATRIX_SLICED, OPERATOR)
{
    Matrix_slice<3> slice( 3, 3, 2);
    EXPECT_EQ(slice(0,0,0), 0);
    EXPECT_EQ(slice(0,0,1), 1);
    EXPECT_EQ(slice(0,1,0), 3);
    EXPECT_EQ(slice(0,1,1), 4);
    EXPECT_EQ(slice(0,2,0), 6);
    EXPECT_EQ(slice(0,2,1), 7);
    EXPECT_EQ(slice(1,0,0), 9);
    EXPECT_EQ(slice(1,0,1), 10);
    EXPECT_EQ(slice(1,1,0), 12);
    EXPECT_EQ(slice(1,1,1), 13);
    EXPECT_EQ(slice(1,2,0), 15);
    EXPECT_EQ(slice(1,2,1), 16);
    EXPECT_EQ(slice(2,0,0), 18);
    EXPECT_EQ(slice(2,0,1), 19);
    EXPECT_EQ(slice(2,1,0), 21);
    EXPECT_EQ(slice(2,1,1), 22);
    EXPECT_EQ(slice(2,2,0), 24);
    EXPECT_EQ(slice(2,2,1), 25);
}


TEST(MATRIX, DEFAULT_CONSTRUCT)
{
    matrix<int,3> m;
    EXPECT_EQ(m.size(), 0);
    EXPECT_EQ(m.extent(0), 0);
    EXPECT_EQ(m.extent(1), 0);
    EXPECT_EQ(m.extent(2), 0);
}

TEST(MATRIX, CONSTRUCT)
{
    matrix<int,3> m(3,3,2);
    EXPECT_EQ(m.size(), 18);
    EXPECT_EQ(m.extent(0), 3);
    EXPECT_EQ(m.extent(1), 3);
    EXPECT_EQ(m.extent(2), 2);
}

TEST(MATRIX, USING_INITIALIZER_LIST)
{
    matrix<int,2> m{{1,2,3},{4,5,6},{7,8,9}};
    EXPECT_EQ(m.extent(0), 3);
    EXPECT_EQ(m.extent(1), 3);
    EXPECT_EQ(m.size(), 9);
}

TEST(MATRIX,INITIALIER_LIST_OPERATOR)
{
    matrix<int,2> m{
        {1,2,3},
        {4,5,6},
        {7,8,9}
        };
    EXPECT_EQ(m.extent(0), 3);
    EXPECT_EQ(m.extent(1), 3);
    EXPECT_EQ(m.size(), 9);
 

}
#include <gtest/gtest.h>
#include "matrix/matrix_slice.h"



TEST(MATRIX_SLICED, CONSTRUCT)
{
    Matrix_slice<3> slice(0, {3,3,2});
    EXPECT_EQ(slice.size, 18);
    EXPECT_EQ(slice.start, 0);
    EXPECT_EQ(slice.extents[0], 3);
    EXPECT_EQ(slice.extents[1], 3);
    EXPECT_EQ(slice.extents[2], 2);
    EXPECT_EQ(slice.strides[0], 1);
    EXPECT_EQ(slice.strides[1], 3);
    EXPECT_EQ(slice.strides[2], 9);

}
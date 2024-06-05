#include <gtest/gtest.h>
#include "matrix/matrix.h"

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
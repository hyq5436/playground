#include "gtest/gtest.h"

TEST(TestDemo, Demo)
{
    int a = 2;
    EXPECT_EQ(a == 2, true);
}

TEST(TestDemo, Error)
{
    int a = 2;
    EXPECT_EQ(a == 2, false);
}

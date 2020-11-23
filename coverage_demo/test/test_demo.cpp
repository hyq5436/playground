#include "gtest/gtest.h"
#include "add.h"

TEST(TestDemo, Add)
{
    EXPECT_EQ(3, add(1, 2));
}

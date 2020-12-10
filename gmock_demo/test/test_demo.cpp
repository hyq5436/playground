#include "gtest/gtest.h"

#include "FooMock.h"
#include "MockTurtle.h"

using namespace seamless;

using ::testing::Assign;
using ::testing::Eq;
using ::testing::Field;
using ::testing::Ge;
using ::testing::InSequence;
using ::testing::Return;

TEST(TestMock, Simple) {
    std::string value = "Hello World!";
    MockFoo mockFoo;

    EXPECT_CALL(mockFoo, getArbitraryString).Times(1).WillOnce(Return(value));
    std::string returnValue = mockFoo.getArbitraryString();
    std::cout << "Return Value: " << returnValue << std::endl;

    EXPECT_CALL(mockFoo, setValue(testing::_));
    mockFoo.setValue(value);

    EXPECT_CALL(mockFoo, setDoubleValues(Eq(1), Ge(1)));
    mockFoo.setDoubleValues(1, 1);
}

TEST(TestField, Simple) {
    MockFoo mockFoo;
    Bar bar;
    bar.num = 0;
    EXPECT_CALL(mockFoo, get(Field(&Bar::num, Ge(0)))).Times(1);
    mockFoo.get(bar);

    bar.num = 1;
    EXPECT_CALL(mockFoo, get(Field(&Bar::num, Ge(0)))).Times(1);
    mockFoo.get(bar);
}

TEST(TestMockTurtle, GetY) {
    MockTurtle mockTurtle;
    EXPECT_CALL(mockTurtle, GetY).Times(2).WillOnce(Return(100));

    EXPECT_EQ(100 == mockTurtle.GetY(), true);
    EXPECT_EQ(0 == mockTurtle.GetY(), true);
}

TEST(TestMockTurtle, GetX) {
    InSequence s;
    MockTurtle mockTurtle;
    EXPECT_CALL(mockTurtle, GetX()).WillOnce(Return(10)).RetiresOnSaturation();
    EXPECT_CALL(mockTurtle, GetX()).WillOnce(Return(20)).RetiresOnSaturation();
    EXPECT_EQ(mockTurtle.GetX(), 10);
    EXPECT_EQ(mockTurtle.GetX(), 20);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
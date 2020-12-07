#include "FooMock.h"

using namespace seamless;
using ::testing::Return;

int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);

    std::string value = "Hello World!";
    MockFoo mockFoo;
    EXPECT_CALL(mockFoo, getArbitraryString()).Times(1).WillOnce(Return(value));

    std::string returnValue = mockFoo.getArbitraryString();

    std::cout << "Return Value: " << returnValue << std::endl;

    return EXIT_SUCCESS;
}
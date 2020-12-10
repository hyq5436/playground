#pragma once

#include <gmock/gmock.h>
#include <string>
#include "FooInterface.h"
namespace seamless {

class MockFoo : public FooInterface {
public:
    MOCK_METHOD0(getArbitraryString, std::string());
    MOCK_METHOD1(setValue, void(std::string& value));
    MOCK_METHOD2(setDoubleValues, void(int x, int y));
    MOCK_METHOD1(get, void(Bar&));
};

}  // namespace seamless
#pragma once

#include <gmock/gmock.h>
#include <string>
#include "FooInterface.h"
namespace seamless {

class MockFoo : public FooInterface {
public:
    MOCK_METHOD0(getArbitraryString, std::string());
};

}  // namespace seamless
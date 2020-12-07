#pragma once

#include <string>

namespace seamless {
class FooInterface {
public:
    virtual ~FooInterface() {}

public:
    virtual std::string getArbitraryString() = 0;
};

}  // namespace seamless

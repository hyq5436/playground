#pragma once

#include <string>

namespace seamless {

struct Bar{
	int num;
};

class FooInterface {
public:
    virtual ~FooInterface() {}

public:
    virtual std::string getArbitraryString() = 0;
    virtual void setValue(std::string& value) = 0;
    virtual void setDoubleValues(int x, int y) = 0;
    virtual void get(Bar&) = 0;
};

}  // namespace seamless

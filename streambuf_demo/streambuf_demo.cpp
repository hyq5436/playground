#include <cstdio>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
    std::stringstream ss;
    std::streambuf* cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());
    std::cout << "std::cout hello world";

    printf("printf %s\n", ss.str().c_str());

    std::cout.rdbuf(cout_buf);

    return 0;
}

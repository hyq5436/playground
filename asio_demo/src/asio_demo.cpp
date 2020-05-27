#include <iostream>
#include <asio.hpp>

void print(const asio::error_code& )
{
    std::cout << "async printf" << std::endl;
}

int main(int argc, char* argv[])
{
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.async_wait(&print);

    io.run();

    return 0;
}

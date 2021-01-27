#include <iostream>
#include <asio.hpp>
#include "server.h"

void print(const asio::error_code& )
{
    std::cout << "async printf" << std::endl;
}

int main(int argc, char* argv[])
{
    asio::io_context io_context;
    udp_server server(io_context);
    io_context.run();

    return 0;
}

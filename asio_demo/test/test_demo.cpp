#include <asio.hpp>
#include "gtest/gtest.h"

TEST(TestDemo, Demo) {
    int a = 2;
    EXPECT_EQ(a == 2, true);
}

TEST(TestDemo, Error) {
    int a = 2;
    EXPECT_EQ(a == 2, true);
}

TEST(ASIO, TcpResolver) {
    asio::io_context io;
    asio::ip::tcp::resolver resolver(io);
    asio::ip::tcp::resolver::query query("www.boost.org", "http");
    asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    asio::ip::tcp::resolver::iterator end;  // End marker.
    while (iter != end) {
        asio::ip::tcp::endpoint endpoint = *iter++;
        std::cout << endpoint << std::endl;
    }

    asio::ip::tcp::socket socket(io);
    asio::connect(socket, resolver.resolve(query));
    std::cout << socket.local_endpoint() << std::endl;
}

TEST(ASIO, TcpIostream) {
    asio::io_context io;
    // asio::ip::tcp::iostream stream("www.boost.org", "http");
    // EXPECT_EQ(!stream, false);

    asio::ip::tcp::iostream stream;
    stream.expires_after(std::chrono::seconds(3));
    stream.connect("www.boost.org", "http");
    stream << "GET /LICENSE_1_0.txt HTTP/1.0\r\n";
    stream << "Host: www.boost.org\r\n";
    stream << "Accept: */*\r\n";
    stream << "Connection: close\r\n\r\n";
    stream.flush();
    std::cout << stream.rdbuf();
}

TEST(Timer, Wait) {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.wait();
    std::cout << "sync wait" << std::endl;
}

void print(const asio::error_code& )
{
    std::cout << "async printf" << std::endl;
}

TEST(Timer, AsyncWait) {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.async_wait(&print);
    io.run();
}

void print_bind(const asio::error_code& , asio::steady_timer& t, int& count)
{
  if (count < 5)
  {
    std::cout << count << std::endl;
    ++count;
    t.expires_at(t.expiry() + std::chrono::seconds(1));
    t.async_wait(std::bind(&print_bind, std::placeholders::_1, std::ref(t), std::ref(count)));
  }

}

TEST(Timer, AsyncWaitBindParam) {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(1));
    int count = 0;
    t.async_wait(std::bind(&print_bind, std::placeholders::_1, std::ref(t), std::ref(count)));
    io.run();
}

#include "printer.h"
TEST(Timer, AsyncWaitBindClassMemeber) {
    asio::io_context io;
    printer p(io);
    io.run();
}

#include "printer2.h"
TEST(Timer, DoubleTimer) {
    asio::io_context io;
    printer2 p(io);
    asio::thread t([&io](){io.run();});
    t.join();
}
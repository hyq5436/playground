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

void print(const asio::error_code&) {
    std::cout << "async printf" << std::endl;
}

TEST(Timer, AsyncWait) {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(5));
    t.async_wait(&print);
    io.run();
}

void print_bind(const asio::error_code&, asio::steady_timer& t, int& count) {
    if (count < 5) {
        std::cout << count << std::endl;
        ++count;
        t.expires_at(t.expiry() + std::chrono::seconds(1));
        t.async_wait(std::bind(&print_bind, std::placeholders::_1, std::ref(t),
                               std::ref(count)));
    }
}

TEST(Timer, AsyncWaitBindParam) {
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(1));
    int count = 0;
    t.async_wait(std::bind(&print_bind, std::placeholders::_1, std::ref(t),
                           std::ref(count)));
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
    asio::thread t([&io]() { io.run(); });
    t.join();
}

TEST(TCP, DISABLED_SyncDaytimeClient) {
    using asio::ip::tcp;
    asio::io_context io;

    std::array<char, 128> buf;
    tcp::resolver resolver(io);
    //auto endpoints = resolver.resolve("time-a-g.nist.gov", "daytime");
    auto endpoints = resolver.resolve("127.0.0.1", "daytime");
    tcp::socket socket(io);
    asio::connect(socket, endpoints);
    do {
        asio::error_code error;

        size_t len = socket.read_some(asio::buffer(buf), error);
        if (error == asio::error::eof)
            break;  // Connection closed cleanly by peer.
        else if (error)
            throw asio::system_error(error);  // Some other error.

        std::cout.write(buf.data(), len);
    } while (true);
}

#include <ctime>
std::string make_daytime_string()
{
    using namespace std;
    time_t now = time(0);
    return ctime(&now);
}

TEST(TCP, DISABLED_SyncDaytimeServer) {
    using asio::ip::tcp;
    asio::io_context io;

    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 13));
    do {
        tcp::socket socket(io);
        acceptor.accept(socket);

        std::string message = make_daytime_string();

        asio::error_code error;
        asio::write(socket, asio::buffer(message), error);
    } while (true);
}

#include "tcp_server.h"
TEST(TCP, DISABLED_AsyncDaytimeServer) {
    using asio::ip::tcp;
    asio::io_context ioc;
    tcp_server server(ioc);
    ioc.run();
}
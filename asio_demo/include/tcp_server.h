#pragma once
#include <asio.hpp>
#include <chrono>
#include <functional>
#include <iostream>

using asio::ip::tcp;

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
    typedef std::shared_ptr<tcp_connection> pointer;

    static pointer create(asio::io_context& io) {
        return pointer(new tcp_connection(io));
    }

    tcp::socket& socket() { return socket_; }

    void start() {
        message_ = make_daytime_string();
        asio::async_write(
            socket_, asio::buffer(message_),
            std::bind(&tcp_connection::handle_write, shared_from_this(),
                      std::placeholders::_1, std::placeholders::_2));
    }

private:
    tcp_connection(asio::io_context& io) : socket_(io) {}

    void handle_write(const asio::error_code, size_t) {}

    std::string make_daytime_string() {
        using namespace std;
        time_t now = time(0);
        return ctime(&now);
    }

    tcp::socket socket_;
    std::string message_;
};

class tcp_server {
public:
    tcp_server(asio::io_context& io)
        : context_(io), acceptor_(io, tcp::endpoint(tcp::v4(), 13)) {
        start_accept();
    }

private:
    void start_accept() {
        tcp_connection::pointer new_connection =
            tcp_connection::create(context_);

        acceptor_.async_accept(
            new_connection->socket(),
            std::bind(&tcp_server::handle_accept, this, new_connection, std::placeholders::_1));
    }

    void handle_accept(tcp_connection::pointer new_connection,
                       const asio::error_code& error) {
        if (!error) {
            new_connection->start();
        }
        start_accept();
    }
    asio::io_context& context_;
    tcp::acceptor acceptor_;
};
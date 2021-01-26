#pragma once
#include <asio.hpp>
#include <functional>
#include <memory>
#include <iostream>

#include "utils.h"

using asio::ip::udp;
using namespace std::placeholders;

class udp_server {
public:
    udp_server(asio::io_context& io_context)
        : socket_(io_context, udp::endpoint(udp::v4(), 13)) {
        start_receive();
    }

private:
    void start_receive() {
        socket_.async_receive_from(
            asio::buffer(recv_buffer_), remote_endpoint_,
            std::bind(&udp_server::handle_receive, this, _1, _2));
    }

    void handle_receive(const asio::error_code& error,
                        std::size_t /* bytes_transferred*/) {
        if (!error) {
            std::shared_ptr<std::string> message(
                new std::string(make_daytime_string()));

            socket_.async_send_to(
                asio::buffer(*message), remote_endpoint_,
                std::bind(&udp_server::handle_send, this, message, _1, _2));
        }
    }

    void handle_send(std::shared_ptr<std::string> /* message */,
                     const asio::error_code& /*error*/,
                     std::size_t /* bytes_transferred*/) {}

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    std::array<char, 1> recv_buffer_;
};

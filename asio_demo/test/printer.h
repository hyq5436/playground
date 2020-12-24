#pragma once
#include <asio.hpp>
#include <chrono>
#include <functional>
#include <iostream>

using namespace std::placeholders;
class printer {
public:
    printer(asio::io_context& io)
        : timer_(io, std::chrono::seconds(1)), count_(0) {
        timer_.async_wait(std::bind(&printer::print, this, _1));
    }

    void print(const asio::error_code&) {
        if (count_ < 5) {
            std::cout << count_ << std::endl;
            ++count_;
            timer_.expires_at(timer_.expiry() + std::chrono::seconds(1));
            timer_.async_wait(std::bind(&printer::print, this, _1));
        }
    }

private:
    asio::steady_timer timer_;
    int count_;
};
#pragma once
#include <asio.hpp>
#include <chrono>
#include <functional>
#include <iostream>

using namespace std::placeholders;
class printer2 {
public:
    printer2(asio::io_context& io)
        : strand_(asio::make_strand(io)),
        timer1_(io, std::chrono::seconds(1)), 
        timer2_(io, std::chrono::seconds(1)),
        count_(0) {
        timer1_.async_wait(asio::bind_executor(strand_, std::bind(&printer2::print1, this)));
        timer2_.async_wait(asio::bind_executor(strand_, std::bind(&printer2::print2, this)));
    }

    ~printer2() {
        std::cout << "Finial count is " << count_ << std::endl;
    }

    void print1() {
        if (count_ < 10) {
            std::cout << "Timer 1: " << count_ << std::endl;
            ++count_;
            timer1_.expires_at(timer1_.expiry() + std::chrono::seconds(1));
            timer1_.async_wait(asio::bind_executor(strand_, std::bind(&printer2::print1, this)));
        }
    }

    void print2() {
        if (count_ < 10) {
            std::cout << "Timer 2: " << count_ << std::endl;
            ++count_;
            timer2_.expires_at(timer2_.expiry() + std::chrono::seconds(1));
            timer2_.async_wait(asio::bind_executor(strand_, std::bind(&printer2::print2, this)));
        }
    }

private:
    asio::strand<asio::io_context::executor_type> strand_;
    asio::steady_timer timer1_;
    asio::steady_timer timer2_;
    int count_;
};
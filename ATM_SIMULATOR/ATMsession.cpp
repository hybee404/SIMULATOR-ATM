// ATMsession.cpp
#include "ATMsession.hpp"
#include "DataBaseHandler.hpp"
#include <iostream>
#include <string>

Session::Session(tcp::socket socket)
    : socket_(std::move(socket))
{
    std::cout << "SESSION[" << ++session_id << "] created" << std::endl;
}

void Session::start_session() {
    do_read(); // Start reading user's input
}

void Session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(
        boost::asio::buffer(data_),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::string request(data_.data(), length);
                process_request(request);
               // Continue the read/write loop
            }
        });
}

void Session::do_write(std::size_t length) {
    auto self(shared_from_this());
    boost::asio::async_write(
        socket_, boost::asio::buffer(data_, length),
        [this, self](boost::system::error_code ec, std::size_t ) {
            if (!ec) {
                do_read(); // Keep reading further input
            }
        });
}

void Session::process_request(std::string& request) {
      initializeDataBase Db; // Your DB handler
      std::string msg;
      
    if(request.empty()){
         return;
        } 
        
        request.erase(0, request.find_first_not_of(" \t\n\r")); 
        request.erase(request.find_last_not_of(" \t\n\r") + 1);

     if (!account_verified_) {
        if (Db.accountExists(request)) { // Check if account exists
            account_verified_ = true;
            current_account_ = request;
            msg = "Account verified. Enter PIN:\n";
             std::fill(data_.begin(), data_.end(), 0); // clear old data
            std::copy(msg.begin(), msg.end(), data_.begin());
                  // send response with correct length
            do_write(msg.size());
        } else {
             msg = "Invalid account. Try again:\n";
             std::fill(data_.begin(), data_.end(), 0); // clear old data
            std::copy(msg.begin(), msg.end(), data_.begin());
                  // send response with correct length
            do_write(msg.size());
             return;
        }
        
        if (!logged_in_) {
        if (Db.verifyPin(request)) { // Check PIN for current account
            logged_in_ = true;
           msg = "Login successful! Welcome.\n";
           std::fill(data_.begin(), data_.end(), 0); // clear old data
            std::copy(msg.begin(), msg.end(), data_.begin());
                  // send response with correct length
            do_write(msg.size());
        } else {
            msg = "Wrong PIN. Try again:\n";
            std::fill(data_.begin(), data_.end(), 0); // clear old data
            std::copy(msg.begin(), msg.end(), data_.begin());
                  // send response with correct length
            do_write(msg.size());
            return;

        }
    }
    }
  
    else {
        // Already logged in, process commands
      msg = "Processing command: " + request + "\n";
      std::fill(data_.begin(), data_.end(), 0); // clear old data
            std::copy(msg.begin(), msg.end(), data_.begin());
                  // send response with correct length
            do_write(msg.size());
        // Call withdraw/checkBalance/etc. here
    }
    request.clear();
  
}
#include "ATMmachine.hpp"


//ATM MACHINE REQUEST-> BANK SERVER RESPOND -> MACHINE READ THE RESPONSE (flow of system)
ATMmachine::ATMmachine(boost::asio::io_context& io_context, const std::string& host, const std::string& port)
        : resolver_(io_context), socket_(io_context)
    {
        connect(host, port); //setting up server to a host
    }

    //Server response to a successful connection
    void ATMmachine::connect(const std::string& host, const std::string& port) {
        try {
            auto endpoints = resolver_.resolve(host, port);
            boost::asio::connect(socket_, endpoints);
            std::cout << "Connected to Bank server at " << host << ":" << port << "\n";
        } catch (std::exception& e) {
            std::cerr << "Connection failed: " << e.what() << "\n";
        }
    }

    void ATMmachine::send_request(const std::string& request) {
        try {
            boost::asio::write(socket_, boost::asio::buffer(request + "\n"));
        } catch (std::exception& e) {
            std::cerr << "Failed to send request: " << e.what() << "\n";
        }
    }


    void ATMmachine::send_response() {
        try {
            boost::asio::streambuf buf;
            boost::asio::read_until(socket_, buf, "\n");
            std::istream res(&buf);
            std::string response;
            std::getline(res, response);
            std::cout << "Bank Server: " << response << "\n";
            
        } catch (std::exception& e) {
            std::cerr << "Failed to read response: " << e.what() << "\n";
        }
    }


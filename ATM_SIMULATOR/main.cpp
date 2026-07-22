#include "ATMserver.hpp"
#include "ATMmachine.hpp"
#include <iostream>
#include <thread>
#include <chrono>


int main(){

    boost::asio::io_context io_context; //client side
    boost::asio::io_context io; //server
    short port = 8080;

    try {
        std::thread server_thread([&]() {
        Server srv(io, port);
        io.run();
    });

   

        std::this_thread::sleep_for(std::chrono::seconds(4));

        ATMmachine atm(io_context, "127.0.0.1", "8080");
        std::string card, pin;
         std::this_thread::sleep_for(std::chrono::seconds(4));
        std::cout << "Enter card number: \n";
        std::getline(std::cin, card);
        std::string request = card;
        atm.send_request(request);
         atm.send_response();
        std::cout << "Enter pin: \n";
        std::getline(std::cin, pin);
        std::string request1 = pin;
         atm.send_request(request1);
        atm.send_response();
        server_thread.join(); //all thread process join in order

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
   

    return 0;
} 




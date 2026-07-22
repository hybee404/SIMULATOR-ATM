#include <iostream>
#include "ATMserver.hpp"
#include "ATMmachine.hpp"
#include "ATMsession.hpp"
#include "DataBaseHandler.hpp"

Server::Server(boost::asio::io_context &io, short port):
acceptConnect(io, tcp::endpoint(tcp::v4(), port)){
    std::cout << "Listening on port " << port << "...\n";
    accept_connection();
}


void Server::accept_connection(){
    acceptConnect.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket){
                if (!ec) {
                    std::cout << "New client: " << socket.remote_endpoint().address().to_string()
                     << ":" << socket.remote_endpoint().port() << "\n";
                    std::make_shared<Session>(std::move(socket))->start_session(); //push connection into thread and accept new one
                } else {
                    std::cout << "Accept error: " << ec.message() << std::endl;
                }
         accept_connection();
        }
    );
}


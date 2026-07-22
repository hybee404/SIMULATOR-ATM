#pragma once
#include <boost/asio.hpp>
#include <memory>

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, short port); 

private:
    void accept_connection(); 

    tcp::acceptor acceptConnect;
};



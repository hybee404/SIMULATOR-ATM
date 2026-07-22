#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

//ATM MACHINE REQUEST-> BANK SERVER RESPOND -> MACHINE READ THE RESPONSE

class ATMmachine {
public:
    ATMmachine(boost::asio::io_context& io_context, const std::string& host, const std::string& port);
    void connect(const std::string& host, const std::string& port);

    void send_request(const std::string& request);

    void send_response();

    void close();
    
private:
    tcp::resolver resolver_;
    tcp::socket socket_;
};

#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <array>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    unsigned int session_count;
    explicit Session(tcp::socket socket);
    void start_session();

private:
    void do_read();
    void do_write(std::size_t length);
    void process_request(std::string& request);

    tcp::socket socket_;
    std::array<char, 1024> data_;
    bool logged_in_ = false;
    std::string current_account_;
    bool account_verified_ = false;
    int session_id = 0;

};

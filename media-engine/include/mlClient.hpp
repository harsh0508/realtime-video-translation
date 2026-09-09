#pragma once

#include <boost/asio.hpp>
#include <boost/asio/local/stream_protocol.hpp>


class MLClient {
    private:
        using stp = boost::asio::local::stream_protocol;
        stp::socket socket;
        std::string socket_path = "/tmp/ml_socket";

    public:
        MLClient(boost::asio::io_context& io_context);
};